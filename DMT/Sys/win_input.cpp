#include "sys_input.h";
#include "..\Sys\sys_public.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"


extern win_info_t win32;

bool Sys_InitKeyboard() {


}

bool Sys_InitController() {


}

bool Sys_InitMouse() {
	HRESULT hr;

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

	if (FAILED(hr = win32.pMouse->SetCooperativeLevel(win32.hWnd,DISCL_EXCLUSIVE | DISCL_FOREGROUND)) ) {
		LogLine("Unable to set cooperation level",Logging::LOG_ERROR);
		return false;
	}

	//Set buffered Data
	DIPROPDWORD bufferProp;
	bufferProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	bufferProp.diph.dwSize = sizeof(DIPROPDWORD);
	bufferProp.diph.dwObj = 0;
	bufferProp.diph.dwHow = DIPH_DEVICE;
	// arbitrary buffer size
	bufferProp.dwData = 128;
	if (FAILED(hr = win32.pMouse->SetProperty(DIPROP_BUFFERSIZE,&bufferProp.diph)) ) {
		LogLine("Unable to set buffered data",Logging::LOG_ERROR);
		return false;
	}
	LogLine("Mouse input setup successfully",Logging::LOG_INFO);
	return true;
}

bool Sys_InitDevices() {
	HRESULT result;
	//http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.directinput8create%28v=vs.85%29.aspx
	if (FAILED(result = DirectInput8Create(GetModuleHandle(NULL),
				DIRECTINPUT_VERSION,
				IID_IDirectInput,
				(void**)&win32.pDI,
				NULL))) {
		LogLine("Unable to create directInput device",Logging::LOG_ERROR);
		return false;
	}
	return true;
}

bool Sys_InitInput() {
	if (!Sys_InitDevices()) {
		return false;
	}
	Sys_InitMouse();
	Sys_InitKeyboard();


	return true;
}
void Sys_PoolInput() {

}
