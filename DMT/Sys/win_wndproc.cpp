#include "..\sys\win_local.h"

LONG WINAPI MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	//TODO
	//Manages windows message events
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}