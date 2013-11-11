#include "input.h"
#include "..\Sys\sys_input.h"


void Input::init() {
	Sys_InputInit();
}

void Input::frame() {
	Sys_InputFrame();
	Sys_InputPoll();
	input_vibration test;
	test.l = 30000;
	test.r = 30000;
	Sys_InputSetRumble(0,&test);
}