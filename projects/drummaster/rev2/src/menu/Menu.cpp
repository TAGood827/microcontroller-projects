#include "Menu.h"

#include "CalibrateChannel.h"
#include "CalibrateChannelSelect.h"
#include "LoadSamples.h"
#include "MainMenu.h"
#include "Stats.h"
#include "VolumeLineIn.h"
#include "VolumeLineOut.h"
#include "VolumePad.h"
#include "VolumePadSelect.h"

using namespace digitalcave;

//Initialize static member variables
char Menu::buf[21];
Hd44780_Teensy* Menu::hd44780 = NULL;
CharDisplay* Menu::display = NULL;
Encoder Menu::encoder(ENC_A, ENC_B);
Bounce Menu::button(ENC_PUSH, 25);

//Initialize static references to menu items
Menu* Menu::calibrateChannel = new CalibrateChannel();
Menu* Menu::calibrateChannelSelect = new CalibrateChannelSelect();
Menu* Menu::loadSamples = new LoadSamples();
Menu* Menu::mainMenu = new MainMenu();
Menu* Menu::stats = new Stats();
Menu* Menu::volumeLineIn = new VolumeLineIn();
Menu* Menu::volumeLineOut = new VolumeLineOut();
Menu* Menu::volumePad = new VolumePad();
Menu* Menu::volumePadSelect = new VolumePadSelect();

Menu* Menu::current = Menu::mainMenu;

Menu::Menu() : encoderState(0){
}

void Menu::poll(){
	current->button.update();
	Menu* newMenu = current->handleAction();
	display->refresh();
	if (newMenu != NULL){
		change(newMenu);
	}
}

void Menu::change(Menu* newMenu){
	current->encoderState = current->encoder.read();
	current = newMenu;
	newMenu->encoder.write(newMenu->encoderState);
}
