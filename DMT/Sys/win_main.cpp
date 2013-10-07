#include <windows.h>
#include <string>
#include <iostream>
#include <D3D11.h>

#include "..\..\..\c++\SiLib\SiLog\logging.h"
#include "..\framework\Common.h"
#include "sys_public.h"

using std::wstring;
extern Common* common;

#define Log Logging::Log
#define LogLine Logging::LogLine

win_info_t win32;
extern Common* common;
void Sys_PumpEvents() {
	MSG msg;
	while( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
		if ( !GetMessage( &msg, NULL, 0, 0 ) ) {
			// Quit msg received
			common->Quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
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
	common->init(0,0,cmdLine);
	Log("log Test\n",Logging::LOG_DEBUG);
	Log("DMTv1.0a\n",Logging::LOG_DEBUG);
	Logging::destroy();
	std::cin.get();
	return 0;

}
