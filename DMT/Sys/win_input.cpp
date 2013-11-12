#include <D3D11.h>
#include <D3DX11tex.h>
#include <DxErr.h>
#include <XInput.h>
#include "sys_input.h";
#include "..\input\input.h"
#include "..\Sys\sys_public.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"


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

void Sys_InputEnableController() {
	XInputEnable(true);
}
void Sys_InputDisableController() {
	XInputEnable(false);
}

bool Sys_InputInitController() {
	Sys_InputEnableController();
	unsigned int numControllers = 0;
	unsigned int controllers[4] = {0,0,0,0};
	XINPUT_STATE state;
	for (int i(0);i < XUSER_MAX_COUNT; ++i) {
		ZeroMemory(&state,sizeof(XINPUT_STATE));
		int result(XInputGetState(i,&state));
		if (result == ERROR_SUCCESS) {
			controllers[numControllers++] = i;
		}
	}
	if (numControllers == 0) {
		Log("Didn't detect any controllers\n",Logging::LOG_INFO); 
		return false;
	}
	win32.numControllers = numControllers;
	Log("Detected ",Logging::LOG_INFO); 
	Log(std::to_string(numControllers),Logging::LOG_INFO);
	Log(" Controllers\n",Logging::LOG_INFO);
	memcpy(&win32.controllers,&controllers,sizeof(unsigned int)*4);
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
	win32.bMouseGrabbed = true;
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

void Sys_InputLost() {
	win32.bMouseGrabbed = false;
	win32.bControllerGrabbed = false;
	//Disable when engine isn't active
	Sys_InputDisableController();
}

void Sys_InputGained() {
	Sys_InputEnableController();
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
	/*
	if (win32.bControllerGrabbed != win32.bGrabController) {
		Sys_InputEnableController();
		win32.bControllerGrabbed = win32.bGrabController;
	}
	*/
}

bool Sys_InputInit() {
	if (!Sys_InputInitDevices()) {
		return false;
	}
	win32.bGrabMouse = true;
	win32.bMouseGrabbed = false;
	Sys_InputInitMouse();
	Sys_InputInitKeyboard();
	Sys_InputInitController();

	return true;
}
static DIDEVICEOBJECTDATA input_buffer[DI_BUFFER_SIZE];
unsigned int Sys_InputPollKeyboard() {
	DWORD numElements(DI_BUFFER_SIZE);
	HRESULT result;

	if (!win32.pKeyboard) {
		Log("No keyboard found\n",Logging::LOG_ERROR);
		return 0;
	}
	result = win32.pKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),input_buffer,&numElements,0);

	if (result != DI_OK) {
		if (result == DI_BUFFEROVERFLOW) {
			Log("Bufferoverflow in PollKeyboard\n",Logging::LOG_ERROR);
		}
		// Keyboard is lost when the window loses focus, try reacquiring it
		result = win32.pKeyboard->Acquire();

		if (!FAILED(result)) {
			// clears the buffer
			win32.pKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),NULL,&numElements,0);
			numElements = 0;
		}
	}

	if (FAILED(result)) {
		return 0;
	}

	return unsigned int(numElements);
}

unsigned int Sys_InputPollMouse() {
	DWORD numElements(DI_BUFFER_SIZE);
	HRESULT result;

	if (!win32.pMouse  || !win32.bMouseGrabbed) {
		Log("Valid mouse not found\n",Logging::LOG_ERROR);
		return 0;
	}
	result = win32.pMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),input_buffer,&numElements,0);

	if (result != DI_OK) {
		if (result == DI_BUFFEROVERFLOW) {
			Log("Bufferoverflow in PollMouse\n",Logging::LOG_ERROR);
		}
		// Mouse is lost when the window loses focus, try reacquiring it
		result = win32.pMouse->Acquire();

		if (!FAILED(result)) {
			// clears the buffer
			win32.pMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA),NULL,&numElements,0);
			numElements = 0;
		}
	}

	if (FAILED(result)) {
		return 0;
	}

	return unsigned int(numElements);
}
void Sys_InputPoll() {
}

void Sys_InputSetRumble(unsigned int which,input_vibration* data) {
	XINPUT_VIBRATION winData;
	winData.wLeftMotorSpeed = data->l;
	winData.wRightMotorSpeed = data->r;
	XInputSetState(which,&winData);
}
