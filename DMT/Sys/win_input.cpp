#include <D3D11.h>
#include <D3DX11tex.h>
#include <DxErr.h>
#include "sys_input.h";
#include "..\Sys\sys_public.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"

#pragma comment(lib, "dinput8.lib")

extern win_info_t win32;
#define DI_BUFFER_SIZE 128

bool Sys_InputInitKeyboard() {
	if (!win32.pDI) {
		return false;
	}
	HRESULT hr;
	if (FAILED(hr = win32.pDI->CreateDevice(GUID_SysKeyboard,&win32.pKeyboard,NULL)) ) {
		LogLine("Unable to create keyboard device",Logging::LOG_ERROR);
		return false;
	}

	if (FAILED(hr = win32.pKeyboard->SetDataFormat(&c_dfDIKeyboard)) ) {
		return false;
	}

	hr = win32.pKeyboard->SetCooperativeLevel(win32.hWnd,DISCL_FOREGROUND 
														| DISCL_NONEXCLUSIVE 
														| DISCL_NOWINKEY);
	if (hr == DIERR_UNSUPPORTED || FAILED(hr)) {
		LogLine("Unable to set keyboard cooperation level",Logging::LOG_ERROR);
		return false;
	}
	//Set buffered data
	DIPROPDWORD bufferProp;
	bufferProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	bufferProp.diph.dwSize = sizeof(DIPROPDWORD);
	bufferProp.diph.dwObj = 0;
	bufferProp.diph.dwHow = DIPH_DEVICE;
	// arbitrary buffer size
	bufferProp.dwData = DI_BUFFER_SIZE;
	if (FAILED(hr = win32.pKeyboard->SetProperty(DIPROP_BUFFERSIZE,&bufferProp.diph)) ) {
		LogLine("Unable to set buffered data for keyboard",Logging::LOG_ERROR);
		return false;
	}

	win32.pKeyboard->Acquire();
	LogLine("Keyboard input setup successfully",Logging::LOG_INFO);
	return true;

}

bool Sys_InputInitController() {


	return true;
}

bool Sys_InputInitMouse() {
	HRESULT hr;
	if (!win32.pDI) {
		return false;
	}

	if (FAILED(hr = win32.pDI->CreateDevice(GUID_SysMouse,&win32.pMouse,NULL)) ) {
		LogLine("Unable to create mouse device",Logging::LOG_ERROR);
		return false;
	}

	//c_dfDIMouse2 can handle 8 button mice
	//c_dfDIMouse can handle 4 button mice
	if (FAILED(hr = win32.pMouse->SetDataFormat(&c_dfDIMouse2)) ) {
		LogLine("Unable to set mouse dataformat",Logging::LOG_ERROR);
		return false;
	}


	//Set buffered Data
	DIPROPDWORD bufferProp;
	bufferProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	bufferProp.diph.dwSize = sizeof(DIPROPDWORD);
	bufferProp.diph.dwObj = 0;
	bufferProp.diph.dwHow = DIPH_DEVICE;
	// arbitrary buffer size
	bufferProp.dwData = DI_BUFFER_SIZE;
	if (FAILED(hr = win32.pMouse->SetProperty(DIPROP_BUFFERSIZE,&bufferProp.diph)) ) {
		LogLine("Unable to set buffered data for mouse",Logging::LOG_ERROR);
		return false;
	}
	Sys_InputCaptureMouse();
	LogLine("Mouse input setup successfully",Logging::LOG_INFO);
	return true;
}

bool Sys_InputInitDevices() {
	HRESULT result;
	//http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.directinput8create%28v=vs.85%29.aspx
	if (FAILED(result = DirectInput8Create(GetModuleHandle(NULL),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&win32.pDI,
				NULL))) {
		DXTrace(__FILE__, (DWORD)__LINE__, result, L"DIRECTInput8Create", true); 
		LogLine("Unable to create directInput device",Logging::LOG_ERROR);
		return false;
	}
	LogLine("Created DI device",Logging::LOG_DEBUG);
	return true;
}

void Sys_InputSetCaptureMouse(bool grab) {
	win32.bGrabMouse = grab;
}

void Sys_InputMouseLost() {
	win32.bMouseGrabbed = false;
}

void Sys_InputCaptureMouse() {
	if (!win32.bGrabMouse)
		return;
	HRESULT hr;
	if (FAILED(hr = win32.pMouse->SetCooperativeLevel(win32.hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND)) ) {
		LogLine("Unable to set mouse cooperation level",Logging::LOG_ERROR);
		DXTrace(__FILE__, (DWORD)__LINE__, hr, L"DIRECTInput8Create", true); 
		return;
	}
	win32.pMouse->Acquire();
}

void Sys_InputFrame() {
	if (win32.bMouseGrabbed != win32.bGrabMouse) {
		Sys_InputCaptureMouse();
		win32.bMouseGrabbed = win32.bGrabMouse;
	}
}

bool Sys_InputInit() {
	if (!Sys_InputInitDevices()) {
		return false;
	}
	win32.bGrabMouse = true;
	win32.bMouseGrabbed = false;
	Sys_InputInitMouse();
	Sys_InputInitKeyboard();


	return true;
}
void Sys_PollInput() {

}
