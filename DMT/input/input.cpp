#include "input.h"
#include "..\Sys\sys_input.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"


void Input::init() {
	Sys_InputInit();
}

void Input::frame() {
	Sys_InputFrame();
	//Poll keyboard
	unsigned int numKeyboardEvents(Sys_InputPollKeyboard());
	if (numKeyboardEvents != 0) {
		Log(std::to_string(numKeyboardEvents),Logging::LOG_INFO);
		LogLine(" keyboard events",Logging::LOG_INFO);
	}
	// Process keyboard events
	
	//Poll mouse
	unsigned int numMouseEvents(Sys_InputPollMouse());
	if (numMouseEvents != 0) {
		Log(std::to_string(numMouseEvents),Logging::LOG_INFO);
		LogLine(" mouse events",Logging::LOG_INFO);
	}

}