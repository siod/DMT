#include <windows.h>
#include <string>
#include <iostream>
#include <D3D11.h>

#include "..\..\..\c++\SiLib\SiLog\logging.h"
#include "..\framework\Common.h"
#include "sys_public.h"

using std::wstring;
extern Common* common;

#ifndef Log
#define Log Logging::Log
#define LogLine Logging::LogLine
#endif

win_info_t win32;
extern Common* common;
void Sys_PumpEvents() {
	while (true) {
		MSG msg;
		while( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
			if ( !GetMessage( &msg, NULL, 0, 0 ) ) {
				// Quit msg received
				common->Quit();
				return;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (!common->Running())
			return;
		common->mainLoop();

	}

}

void Sys_Quit() {
	ExitProcess(0);

}

void Sys_Init() {


}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	LogLine("DMTv1.0a",Logging::LOG_DEBUG);
	common->init(0,0,cmdLine);
	Sys_PumpEvents();
	Logging::destroy();
	std::cin.get();
	return 0;

}
