#ifndef _SYS_PUBLIC_H
#define _SYS_PUBLIC_H
#include <windows.h>
#include <D3D11.h>
#include <dinput.h>

typedef struct {
	HWND hWnd;
	HINSTANCE hInstance;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pContext;
	IDXGISwapChain*  pSwapChain;

	LPDIRECTINPUT8			pDI;
	LPDIRECTINPUTDEVICE8	pMouse;
	LPDIRECTINPUTDEVICE8	pKeyboard;
	bool bMouseGrabbed;
	bool bGrabMouse;
	bool bControllerGrabbed;
	bool bGrabController;
	unsigned int numControllers;
	unsigned int controllers[4];

	bool windowRegistered;

} win_info_t;

// quits the game
void Sys_Quit();
void Sys_Init();

#endif