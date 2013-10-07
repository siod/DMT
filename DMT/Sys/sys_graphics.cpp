

#include <D3D11.h>
#include <D3DX11tex.h>
#include <DxErr.h>
#include "..\Sys\sys_public.h"
#include "..\Sys\sys_graphics.h"
#include "..\framework\typedefs.h"
#include "..\framework\math.h"
#include "..\renderer\vertexBuff.h"
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
	scd.SampleDesc.Count   = params.numSamples;
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

void Sys_ShutdownGraphics() {


}

/*
bool Sys_CreateTextureBuffer() {
	return true;

}
*/


DXGI_FORMAT Sys_ConvertBufferFormat(int engineFormat) {
	//returns a converted engine format to the OS format
	//TODO
	return DXGI_FORMAT_R32G32B32A32_FLOAT;
}


Texture Sys_LoadTextureFromFile(const SiString& filename,int format) {
		
	Texture newTexture;
	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory( &loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO) );
	loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	loadInfo.Format = Sys_ConvertBufferFormat(format);
	HR(D3DX11CreateShaderResourceViewFromFile(win32.pDevice, convertToWideString(filename).c_str(),
											&loadInfo, NULL, &newTexture.res, NULL));
	return newTexture;

}
void Sys_ReleaseTexture(Texture& texture) {
	if (texture.res == NULL) {
		return;
	}
	texture.res->Release();
	texture.res = NULL;
}
Texture Sys_LoadTexture() {
	//TODO
	Texture tmp;
	tmp.res = NULL;
	return tmp;
}

D3D11_USAGE sys_buffer_usage_lt[] = {
	D3D11_USAGE_DEFAULT,
	D3D11_USAGE_IMMUTABLE,
	D3D11_USAGE_DYNAMIC,
	D3D11_USAGE_STAGING };

D3D11_BIND_FLAG sys_buffer_bind_lt[] = {
	D3D11_BIND_VERTEX_BUFFER,
	D3D11_BIND_INDEX_BUFFER,
	D3D11_BIND_CONSTANT_BUFFER,
	D3D11_BIND_SHADER_RESOURCE,
	D3D11_BIND_STREAM_OUTPUT,
	D3D11_BIND_RENDER_TARGET,
	D3D11_BIND_DEPTH_STENCIL 
};

void Sys_ConvertBufferFormat(D3D11_BUFFER_DESC &sysbuffer, const RenderBuffer &engineBuffer) {
	sysbuffer.Usage = sys_buffer_usage_lt[engineBuffer.usage];
    sysbuffer.BindFlags = sys_buffer_bind_lt[engineBuffer.type];
    sysbuffer.ByteWidth = engineBuffer.size;
	sysbuffer.CPUAccessFlags = (engineBuffer.cpu_writable) ? D3D11_CPU_ACCESS_WRITE : D3D11_CPU_ACCESS_READ;
	sysbuffer.MiscFlags = 0;
}

bool Sys_CreateBuffer(RenderBuffer* buffer,void* data) {
	D3D11_BUFFER_DESC bd;
	Sys_ConvertBufferFormat(bd,*buffer);
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	HR(win32.pDevice->CreateBuffer(&bd,&initData,&buffer->data.res));
	return true;
}