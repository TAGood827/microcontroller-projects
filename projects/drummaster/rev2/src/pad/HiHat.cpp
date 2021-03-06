#include "HiHat.h"

using namespace digitalcave;

#define HIHAT_SPECIAL_CHIC			16
#define HIHAT_SPECIAL_SPLASH		17

//2 raised to this number is how many samples we keep in the running pedal position average
#define AVERAGE_PEDAL_COUNT_EXP		8

HiHat::HiHat(uint8_t piezoMuxIndex, uint8_t pedalMuxIndex, uint8_t switchMuxIndex, uint8_t doubleHitThreshold, double fadeGain) : 
		Cymbal(piezoMuxIndex, switchMuxIndex, doubleHitThreshold, fadeGain),
		averagePedalPosition(0),
		lastChicTime(0),
		lastChicVolume(0),
		lastSampleChange(0),
		pedalMuxIndex(pedalMuxIndex) {

}

void HiHat::poll(){
	readSwitch(switchMuxIndex);
	readPedal(pedalMuxIndex);
	
	//We have just tightly closed the pedal; play the chic sound if it is fast enough.  The 
	// volume will depend on how fast it was closed (i.e. what the average position was prior to the close)
	if ((!lastSwitchValue && switchValue) || (pedalPosition <= 1 && lastPedalPosition > 1)){
		double volume = (getAveragePedalPosition() / 16.0 - 0.2);
		if (volume > 0 && lastChicTime + 200 < millis()){
			Sample::startFade(padIndex, 0.95);
			lastSample = Sample::findAvailableSample(padIndex, volume);
			lastSample->play(lookupFilename(volume, HIHAT_SPECIAL_CHIC), padIndex, volume, 1);
			lastChicTime = millis();
			lastChicVolume = volume;
		}
		else {
			Sample::startFade(padIndex, getFadeGain());
		}
	}

	double volume = readPiezo(piezoMuxIndex);
	if (volume > 0){
		if (volume >= 5.0) volume = 5.0;

		lastSample = Sample::findAvailableSample(padIndex, volume);
		lastSample->play(lookupFilename(volume), padIndex, volume);
	}
	
	Sample::processFade(padIndex);
}

uint8_t HiHat::getAveragePedalPosition(){
	return averagePedalPosition >> AVERAGE_PEDAL_COUNT_EXP;
}

void HiHat::readPedal(uint8_t muxIndex){
	lastPedalPosition = pedalPosition;
	
	if (switchValue) {
		pedalPosition = 0x00;		//Switch state 1 means tightly closed
	}
	else {
		//Disable both MUXs
		digitalWriteFast(ADC_EN, MUX_DISABLE);
		digitalWriteFast(DRAIN_EN, MUX_DISABLE);
		
		//Set Sample
		digitalWriteFast(MUX0, muxIndex & 0x01);
		digitalWriteFast(MUX1, muxIndex & 0x02);
		digitalWriteFast(MUX2, muxIndex & 0x04);
		digitalWriteFast(MUX3, muxIndex & 0x08);
		
		//Enable ADC MUX...
		digitalWriteFast(ADC_EN, MUX_ENABLE);

		//... read value...
		int16_t currentValue = adc->analogRead(ADC_INPUT);
		
		//... and disable MUX again
		digitalWriteFast(ADC_EN, MUX_DISABLE);
		
		//Enable drain for a bit to ensure quick response times (since the HiHat 
		// Pedal channel goes through peak detection circuit... it would probably
		// have been fine to just use a switching channel instead of a filtered channel).
		digitalWriteFast(DRAIN_EN, MUX_ENABLE);
		
		//currentValue is a 10 bit ADC variable; we want to return a 4 bit value from 0x00-0x0F.
		// Thus we need to right shift 6 bits (10 - 4 = 6).  We do a bitwise and just to be safe.
		pedalPosition = (currentValue >> 6) & 0x0F;
		
		//We reserve position 0 for tightly closed (from the switch parameter)
		if (pedalPosition == 0) pedalPosition = 1;
	}

	//Keep a running average of 2^AVERAGE_PEDAL_COUNT_EXP previous pedal positions
	averagePedalPosition = averagePedalPosition + pedalPosition - (averagePedalPosition >> AVERAGE_PEDAL_COUNT_EXP);
}

inline uint8_t getClosestVolume(int8_t closestVolume, uint8_t pedalPositionIndex, uint16_t* sampleVolumes){
	if (sampleVolumes[pedalPositionIndex] == 0) return 0xFF;
	
	//Start at the current bucket; if that is not a match, look up and down until a match is found.  At 
	// most this will take 16 tries (since there are 16 buckets)
	for(uint8_t j = 0; j < 16; j++){
		if (((closestVolume + j) <= 0x0F) && (sampleVolumes[pedalPositionIndex] & _BV(closestVolume + j))) {
			return closestVolume + j;
		}
		else if (((closestVolume - j) >= 0x00) && (sampleVolumes[pedalPositionIndex] & _BV(closestVolume - j))) {
			return closestVolume - j;
		}
	}
	
	return 0xFF;
}

char* HiHat::lookupFilename(double volume){
	return lookupFilename(volume, 0);
}

char* HiHat::lookupFilename(double volume, uint8_t hihatSpecial){
	//Limit volume from 0 to 1
	if (volume < 0) volume = 0;
	else if (volume >= 1.0) volume = 1.0;

	//We find the closest match in sampleVolumes for volume (and possibly pedal position if this is not a special sound)
	uint8_t closestVolume = volume * 16;		//Multiply by 16 to get into the 16 buckets of the samples
	
	if (hihatSpecial == HIHAT_SPECIAL_CHIC || hihatSpecial == HIHAT_SPECIAL_SPLASH){
		closestVolume = getClosestVolume(closestVolume, hihatSpecial, sampleVolumes);
		if (closestVolume == 0xFF){
			return NULL;
		}
		else {
			snprintf(filenameResult, sizeof(filenameResult), "%s%s%X.RAW", filenamePrefix, hihatSpecial == HIHAT_SPECIAL_CHIC ? "K" : "P", closestVolume);
		}
	}
	else {
		//Find the closes match in pedal position.
		int8_t closestPedalPosition = pedalPosition;	//Pedal position is already a 4 bit number

		//Pedal position is more important than velocity; thus, we look for the closest match on
		// position first, and then once we find any sample closest to the selected pedal position,
		// we then look to find the closest velocity sample within that position.
		for(uint8_t i = 0; i < 16; i++){
			//First we check if there is anything in the sampleVolumes array at this index; if so, we go with it.
			if (((closestPedalPosition + i) <= 0x0F) && (sampleVolumes[closestPedalPosition + i])) {
				//Remember what pedal position we are looking at
				closestPedalPosition = closestPedalPosition + i;
				closestVolume = getClosestVolume(closestVolume, closestPedalPosition, sampleVolumes);
				break;
			}
			//Likewise on the low side.
			if (((closestPedalPosition - i) <= 0x0F) && (sampleVolumes[closestPedalPosition - i])) {
				//Remember what pedal position we are looking at
				closestPedalPosition = closestPedalPosition - i;
				closestVolume = getClosestVolume(closestVolume, closestPedalPosition, sampleVolumes);
				break;
			}
		}

		snprintf(filenameResult, sizeof(filenameResult), "%s%X%X.RAW", filenamePrefix, closestPedalPosition, closestVolume);
	}
	
	return filenameResult;
}

void HiHat::loadSamples(char* filenamePrefix){
	//Clear the filenames
	for (uint8_t i = 0; i < sizeof(this->filenamePrefix); i++){
		this->filenamePrefix[i] = 0x00;
	}
	for (uint8_t i = 0; i < sizeof(this->filenameResult); i++){
		this->filenameResult[i] = 0x00;
	}	
	
	//The filename prefix must be at least three chars
	if (strlen(filenamePrefix) < 3) return;
	
	strncpy(this->filenamePrefix, filenamePrefix, FILENAME_PREFIX_STRING_SIZE - 1);
	
	//Reset sampleVolumes
	for (uint8_t i = 0; i < 18; i++){
		sampleVolumes[i] = 0x00;
	}

	SerialFlash.opendir();
	while (1) {
		char filename[16];
		unsigned long filesize;

		if (SerialFlash.readdir(filename, sizeof(filename), filesize)) {
			uint8_t filenamePrefixLength = strlen(filenamePrefix);
			if (filenamePrefixLength > 6) filenamePrefixLength = 6;
			
			//Check that this filename starts with the currently assigned filename prefix
			if (strncmp(filenamePrefix, filename, filenamePrefixLength) != 0) {
				continue;
			}
			
			//Check that the filename pedal position is valid (0..F).  The pedal position is the first character after the prefix.
			char filePedalPosition = filename[filenamePrefixLength];
			uint8_t pedalPosition;
			if (filePedalPosition >= '0' && filePedalPosition <= '9') pedalPosition = filePedalPosition - 0x30;
			else if (filePedalPosition >= 'A' && filePedalPosition <= 'F') pedalPosition = filePedalPosition - 0x37;
			else if (filePedalPosition == 'K') pedalPosition = HIHAT_SPECIAL_CHIC;
			else if (filePedalPosition == 'P') pedalPosition = HIHAT_SPECIAL_SPLASH;
			else {
				continue;	//Invalid volume
			}
			
			//Check that the filename volume is valid (0..F).  The volume is the second character after the prefix.
			char fileVolume = filename[filenamePrefixLength + 1];
			uint8_t volume;
			if (fileVolume >= '0' && fileVolume <= '9') volume = fileVolume - 0x30;
			else if (fileVolume >= 'A' && fileVolume <= 'F') volume = fileVolume - 0x37;
			else {
				continue;	//Invalid volume
			}
			sampleVolumes[pedalPosition] |= _BV(volume);
		} 
		else {
			break; // no more files
		}
	}
}
