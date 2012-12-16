

#include <D3D11.h>
#include <DxErr.h>
#include "..\Sys\sys_public.h"
#include "..\Sys\sys_graphics.h"
extern win_info_t win32;
#define DMT_WINDOW_CLASS_NAME L"DMT"
#define DMT_NAME L"DMT v0.1a"

LONG WINAPI MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d11.lib" )
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment( lib, "d3dx11d.lib" )
#else
#pragma comment( lib, "d3dx11.lib" )
#endif
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 

void Sys_InitWindowClass() {
	if (win32.windowRegistered)
		return;
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = win32.hInstance;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = DMT_WINDOW_CLASS_NAME;

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass FAILED", 0, 0);
		PostQuitMessage(0);
	}
	win32.windowRegistered = true;
}


void Sys_CreateWindow(driver_params_t params) {
	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, params.width, params.height };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	win32.hWnd = CreateWindow(DMT_WINDOW_CLASS_NAME, DMT_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, win32.hInstance, NULL); 
	if( !win32.hWnd )
	{
		MessageBox(0, L"CreateWindow FAILED", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(win32.hWnd, SW_SHOW);
	UpdateWindow(win32.hWnd);

}
void Sys_InitGraphicsDriver(driver_params_t params) {
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd,sizeof(scd));

	scd.BufferDesc.Width  = params.width;
	scd.BufferDesc.Height = params.height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// No multisampling.
	scd.SampleDesc.Count   = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount  = 1;
	scd.OutputWindow = win32.hWnd;
	scd.Windowed     = true;
	scd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags        = 0;
	D3D_FEATURE_LEVEL featureLvl;
	HR(D3D11CreateDeviceAndSwapChain(
		0,//Default device
		D3D_DRIVER_TYPE_HARDWARE,
		0,//Not using software rasterizer
		params.deviceFlags,
		NULL, 0, // Default featureLevel Array
		D3D11_SDK_VERSION,
		&scd,
		&win32.pSwapChain,
		&win32.pDevice,
		&featureLvl,
		&win32.pContext) );

}

void Sys_InitGraphics(driver_params_t params) {
	Sys_InitWindowClass();
	Sys_CreateWindow(params);
	Sys_InitGraphicsDriver(params);
}