/*
 * Drum Master - controller for up to 32 + 8 sensors.
 * Copyright 2008 - 2009 Wyatt Olson <wyatt.olson@gmail.com>
 * 
 * At a very high level, Drum Master will listen to a series of sensors (both analog, via piezo
 * transducers, and digital, via grounding pullup resistors), and report the values back to the
 * computer via the serial port.	Each signal is sent in a packet, using a binary protocol 
 * consisting of 2 bytes / packet:
 *
 *		|cccccckk|vvvvvvvv|
 *      <channel:6><checksum:2><value:8>
 *
 * Each portion of the packet is described below:
 *		<channel> is the 6 bit representation of a channel number between 0x00 and 0x27 (39).  
 *				Analog channels are 0x00..0x1F, and digital channels are 0x20..0x27.
 *		<value> is the 8 bit representation of the actual analog value between 0x0 and 0xFF.
 *		<checksum> is the 2 bit checksum on the rest of the packet, calculated using the 
 *				2 bit parity word algorithm.  Each 2-bit chunk of the packet is XOR'd together. 
 *				The slave software will XOR all 8 2 bit words together; if the result is not 0x0
 *				then we know there was an error in transmission.
 *
 * Slave software, running on the computer, must take these data packets and map them to digital
 * audio samples, based on the channel, velocity, and current state of the program.
 *
 * For more information, please visit http://drummaster.digitalcave.ca.
 * 
 * Changelog:
 * 1.3.0.0 - April 2013:		-Complete rewrite, after using logic probes to verify timings.
								-Completely removed reliance on timer code.  This was 64 / 32 bit code, and was
								extremely expensive to run (64 bit arithmetic, even simple adds, can take upwards as 
								long as the ADC conversions themselves)
								-Eliminated reliance on triggers; use the ADC for all values now.
								-All variables are now 8 bit
								-Velocity is now 8 bit (drop the 2 LSB of the 10 bit value).  The bottom two bits
								were just noise anyway, so why waste space sending them?
								-Simplified transmission protocol, reducing size to 2 bytes from 3.
								-Possibly reducing number of inputs from 32 to 8 (or 16?)  Need to test for speed...
 									
 * 1.2.0.2 - January 23 2011:	-For digital channels, send 0x1 for closed (button pressed) and 0x0 for button open. 
 * 								This is backwards from the logical state (since we use pullup resistors forcing 
 * 								the value to logic HIGH for open and logic LOW for closed; however it makes
 * 								the slave software a bit easier to understand.
 * 1.2.0.1 - October 15 2010:	-Further bugfixes; now things are working (somewhat decently) with Slave software
 *								version 2.0.1.1.  Main problem was a driver issue for the MUX selector where the 
 *								endian-ness of the selector was backwards.
 * 1.2.0.0 - Aug 25 2010:		-Converting to plain AVR code from Arduino, to hopefully see a speedup
 *								in analog reading and serial communication.
 * 1.1.2.0 - Sept 12 2009:		-Fixed a bug with active channels which did not send data if the value
 *								was below the trigger threshold.
 *								-Adjusted active channel values to be more verbose in sending data, so
 *								that the slave program has better data to work with.	This has resulted
 *								in substantially more realistic hi hat behaviour.
 * 1.1.1.0 - July 2 2009:		-Adjusted #define values to better suit hardware.
 *								-Added more comments for all #define values to indicate more clearly
 *								what each does.
 *
 * 1.1.0.0 - June ? 2009:		-Added the concept of 'active channels'; channels that report
 *								a value X number of times in a row are assumed to be active;
 *								this is used for things like analog hi-hat controllers, where
 *								we want to have a continuous report of changes, but not
 *								constantly waste time on the serial port if there are no changes.
 *								-Combine multiple simultaneous strikes into a single data packet
 *								to reduce the number of expensive (~20ms each) serial writes.	 
 *								This has successfully decreased latency to unnoticable levels
 *								when there are multiple simultaneous strikes.
 *
 * 1.0.0.0 - May ? 2008:		-Initial version.	 Works fine for basic drumming requirements.
 */

#include <avr/io.h>
#include <stdlib.h>
#include "../lib/analog/analog.h"
#include "../lib/serial/serial.h"

//The smallest ADC value which we will report
#define MIN_VELOCITY 5

//This is used for a number of data buffers.	It should be set to the number of channels (this is
// 40 in default hardware).	 You will only want to change this if you have modified / custom hardware.
#define BUFFER_SIZE 40


//Is it time to read active channels?	 Set to true at the beginning of a loop if this is the case, and
// reset at the end.
uint8_t read_active_channels;

//Active counter.	 Increments each cell by one each time a value for the corresponding channel is
// read; if there is no value read, it will reset the cell to 0.	Once a given cell gets above
// MIN_ACTIVE_CHANNEL_POLL_COUNT, we will poll on a less frequent basis, and will only report large
// changes over the serial port.
uint8_t consecutive_reads[BUFFER_SIZE];

//Keep track of active channels, to reduce computations.	Once a channel is set to be active,
// only a reset will change it back.
uint8_t active_channel[BUFFER_SIZE];

//What was the last value read from each channel?
uint8_t last_value[BUFFER_SIZE];

//When we send a value, we reset this to a large positive number (the exact value depends on how
// long you want to debounce for).  Each iteration after, we decrement.  Once we hit zero we can
// potentially read the value again.
uint8_t debounce_counter[BUFFER_SIZE];

/*
 * Sets pins S2 - S0 to select the multiplexer output.
 */
void set_port(uint8_t port){
	//Set bits based on channel, making sure we don't set more than 3 bits.
	//For PCB layout simplicity, we designed the board such that the MSB is 
	// PINB0 and LSB is PINB2.  Thus, we need to flip the 3-bit word.
	PORTB = ((port & 0x1) << 2) | (port & 0x2) | ((port & 0x4) >> 2);
}

/*
 * Convert from a bank / port tuple to single channel number (value from 0 - 39 inclusive)
 * for sending to Drum Slave software.
 */
uint8_t get_channel(uint8_t bank, uint8_t port){
	return (bank << 3) | port;
}

/*
 * Reads the input and returns the 8 MSB.
 */
uint8_t get_velocity(uint8_t pin){
	return (analog_read_p(pin) >> 2);
}

/*
 * Sends data.  Channel is a 6 bit number, between 0x00 and 0x27 inclusive.  Velocity is a 8 bit number.
 */
void send_data(uint8_t channel, uint8_t velocity){
	uint8_t packet;
	uint8_t checksum = 0x0;
	
	//First packet consists of 6 channel bits, and (eventually) 2 checksum bits.
	packet = ((channel << 0x02) & 0xFC);
	
	//Add channel to checksum
	checksum ^= channel >> 0x04;
	checksum ^= (channel >> 0x02) & 0x03;
	checksum ^= channel & 0x3;
	
	//Add velocity to packet
	checksum ^= velocity >> 0x06;
	checksum ^= (velocity >> 0x04) & 0x03;
	checksum ^= (velocity >> 0x02) & 0x03;
	checksum ^= velocity & 0x03;
	
	packet |= checksum;
	serial_write_c(packet);

	//Second packet consists only of 8 bits data.
	serial_write_c(velocity);
}

int main (void){
	//Init libraries	
	uint8_t apins[1];
	apins[0] = 0;
	analog_init(apins, 1, ANALOG_AREF);
	
	serial_init_b(57600);

	//Iterators for port and bank; channel and velocity are the selector 
	// address (channel) and velocity respectively;
	uint8_t port, bank = 0, channel, velocity;

	//Set the analog triggers (2::5) and digital input (6) to input mode.
	DDRD &= ~(_BV(DDD2) | _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6));

	//The three MUX selector switches need to be set to output mode
	DDRB |= _BV(DDB0) | _BV(DDB1) | _BV(DDB2);

	//Initialize array counters
	for (port = 0; port < BUFFER_SIZE; port++){
		//Initialize the active consecutive reads counter
		consecutive_reads[port] = 0;

		//Reset the active channels to all 0
		active_channel[port] = 0;
	}

	//Main program loop
	while (1){
		for (bank = 0x00; bank < 0x05; bank++){	//bank is one ADC (for 0x00..0x03) or digital (0x04) input
			for (port = 0x00; port < 0x08; port++){	//port is one channel on a multiplexer
				set_port(port);

				//Read the analog pins
				channel = get_channel(bank, port);
		
				if (debounce_counter[channel] > 0){
					debounce_counter[channel]--;
				}
				else {
					if (bank < 0x04){
						velocity = get_velocity(bank);
						if (velocity >= MIN_VELOCITY || channel == 0x02){	//Channel 2 is Hi Hat Pedal, which is active channel.
							//We watch the values, and send as it starts to decrease
							if (last_value[channel] > velocity){
								send_data(channel, last_value[channel]);
								debounce_counter[channel] = 0xFF;	//TODO Change this based on actual measurements.
							}
							else {
								last_value[channel] = velocity;
							}
						}
					}
					else if (bank == 0x04){
						//Read the digital pins
						channel = get_channel(bank, port);
				
						//Remember that digital switches in drum master are reversed, since they 
						// use pull up resisitors.	Logic 1 is open, logic 0 is closed.	 When 
						// sending the readings, we invert the value to make this easy to keep straight.
						velocity = (PIND & _BV(PIND6)) >> PIND6;
						if (velocity != last_value[channel]){
							send_data(channel, (velocity == 0x00 ? 0xFF : 0x00)); //Invert the value
							debounce_counter[channel] = 0xFF;	//TODO Change this based on actual measurements.
							last_value[channel] = velocity;
						}
					}
				}
			}
		}
	}
}

