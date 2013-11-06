#include "..\sys\win_local.h"
#include "..\framework\Common.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"
#include "sys_input.h"

#ifndef Log
#define Log Logging::Log
#define LogLine Logging::LogLine
#endif

extern Common* common;
LONG WINAPI MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	//TODO
	//Manages windows message events
	switch (uMsg) {
		case WM_CLOSE:
			LogLine("Close message received",Logging::LOG_INFO);
			common->Quit();
			break;

		case WM_ACTIVATE: {
			int active;
			bool minimized;
			active = LOWORD(wParam);
			minimized = HIWORD(wParam);
			bool isActive = (active != WA_INACTIVE);
			if (isActive) {
				Sys_InputMouseLost();
			}
			break;
		  }
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			break;
		default:
			//LogLine("Unknown Window message",Logging::LOG_ERROR);
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}