#include "input.h"
#include "..\Sys\sys_input.h"


void Input::init() {
	Sys_InputInit();
}

void Input::frame() {
	Sys_InputFrame();
}