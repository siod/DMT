

#include <D3D11.h>
#include <D3DX11tex.h>
#include <DxErr.h>
#include "..\Sys\sys_public.h"
#include "..\Sys\sys_graphics.h"
#include "..\framework\typedefs.h"
#include "..\framework\math.h"
#include "..\renderer\vertexBuff.h"
#include "..\renderer\renderView.h"
#include "..\renderer\Texture.h"
#include "..\renderer\Shader.h"

#include "..\..\..\c++\SiLib\SiLog\logging.h"

extern win_info_t win32;
#define DMT_WINDOW_CLASS_NAME L"DMT"
#define DMT_NAME L"DMT v0.1a"

LRESULT CALLBACK MainWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

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
		LogLine("RegisterClass FAILED",Logging::LOG_ERROR);
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
		LogLine("CreateWindow FAILED",Logging::LOG_ERROR);
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
	scd.Flags        = (params.deviceFlags) ? D3D11_CREATE_DEVICE_DEBUG: 0;
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

	ID3D11RasterizerState* pRState(NULL);
	D3D11_RASTERIZER_DESC rDesc;
	ZeroMemory(&rDesc,sizeof(rDesc));
	//rDesc.CullMode = D3D11_CULL_NONE;
	rDesc.CullMode = D3D11_CULL_BACK;
	//rDesc.FillMode = D3D11_FILL_WIREFRAME;
	rDesc.FillMode = D3D11_FILL_SOLID;
	win32.pDevice->CreateRasterizerState(&rDesc,&pRState);
	win32.pContext->RSSetState(pRState);


	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc,sizeof(dsDesc));
	//Depth test params
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//Stencil test params
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	ID3D11DepthStencilState * pDSState(NULL);
	win32.pDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	win32.pContext->OMSetDepthStencilState(pDSState, 1);


}

void Sys_InitGraphics(driver_params_t params) {
	Sys_InitWindowClass();
	Sys_CreateWindow(params);
	Sys_InitGraphicsDriver(params);
}

void Sys_ShutdownGraphics() {


}

void Sys_SwapAndDisplay() {
	win32.pSwapChain->Present(0,0);
}

/*
bool Sys_CreateTextureBuffer() {
	return true;

}
*/

const D3D11_USAGE sys_buffer_usage_lt[] = {
	D3D11_USAGE_DEFAULT,
	D3D11_USAGE_IMMUTABLE,
	D3D11_USAGE_DYNAMIC,
	D3D11_USAGE_STAGING 
};

const D3D11_BIND_FLAG sys_buffer_bind_lt[] = {
	D3D11_BIND_VERTEX_BUFFER,
	D3D11_BIND_INDEX_BUFFER,
	D3D11_BIND_CONSTANT_BUFFER,
	D3D11_BIND_SHADER_RESOURCE,
	D3D11_BIND_STREAM_OUTPUT,
	D3D11_BIND_RENDER_TARGET,
	D3D11_BIND_DEPTH_STENCIL 
};

const unsigned int sys_buffer_cpu_access_lt[] = {
	0,
	D3D11_CPU_ACCESS_READ,
	D3D11_CPU_ACCESS_WRITE
};

void Sys_ConvertBufferFormat(D3D11_BUFFER_DESC &sysbuffer, const Buffer &engineBuffer) {
	sysbuffer.Usage = sys_buffer_usage_lt[engineBuffer.usage];
    sysbuffer.BindFlags = sys_buffer_bind_lt[engineBuffer.type];
    sysbuffer.ByteWidth = engineBuffer.size*max(engineBuffer.stride,1u);
	sysbuffer.CPUAccessFlags = sys_buffer_cpu_access_lt[engineBuffer.cpu_access];
	sysbuffer.MiscFlags = 0;
	sysbuffer.StructureByteStride = engineBuffer.stride;
}

DXGI_FORMAT Sys_ConvertTextureFormat(const int engineFormat) {
	//returns a converted engine format to the OS format
	//TODO
	switch (engineFormat) {
		case 0:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case 1:
			return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case 2:
			return DXGI_FORMAT_R8G8B8A8_UNORM;
		case 3:
			return DXGI_FORMAT_R32_UINT;
		default:
			Log("Invalid call to ConvertTextureFormat\n",Logging::LOG_ERROR);
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
	}
}


void Sys_ConvertTextureFormat(D3D11_TEXTURE2D_DESC &desc,const Texture &engineDesc) {
	desc.Height = engineDesc.height;
	desc.Width = engineDesc.width;
	desc.MipLevels = engineDesc.mipLevels;
	desc.ArraySize = 1;
	desc.Format = Sys_ConvertTextureFormat(engineDesc.format);
	desc.SampleDesc.Count =1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = sys_buffer_usage_lt[engineDesc.usage];
	desc.BindFlags = sys_buffer_bind_lt[engineDesc.bindFlags];
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
}

void Sys_CreateTexture(Texture &tex) {
	D3D11_TEXTURE2D_DESC desc;
	Sys_ConvertTextureFormat(desc,tex);
	HR(win32.pDevice->CreateTexture2D(&desc,NULL,&tex.texture.res));
}

void Sys_LoadTextureFromFile(Texture &texture,const SiString& filename) {
		
	/*
	Sys_texture_t newTexture;
	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory( &loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO) );
	loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	loadInfo.Format = Sys_ConvertTextureFormat(format);
	HR(D3DX11CreateShaderResourceViewFromFile(win32.pDevice, convertToWideString(filename).c_str(),
											&loadInfo, NULL, &newTexture.res, NULL));
											*/

}

void Sys_ReleaseTexture(Sys_texture_t& texture) {
	if (texture.res == NULL) {
		return;
	}
	texture.res->Release();
	texture.res = NULL;
}

Sys_texture_t Sys_LoadTexture() {
	//TODO
	Sys_texture_t tmp;
	tmp.res = NULL;
	return tmp;
}

void Sys_createShaderResource(renderView &view) {



}

void Sys_CreateScreenBuffers(renderView &view) {
	ID3D11Texture2D* backBuffer;
	HR(win32.pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(win32.pDevice->CreateRenderTargetView(backBuffer,0,&view.res.target));
	D3D11_DEPTH_STENCIL_VIEW_DESC stencilDesc;
	ZeroMemory(&stencilDesc,sizeof(stencilDesc));
	stencilDesc.Format = Sys_ConvertTextureFormat(view.stencilTexture->format);
	stencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	stencilDesc.Texture2D.MipSlice = 0;
	HR(win32.pDevice->CreateDepthStencilView(view.stencilTexture->texture.res,&stencilDesc,&view.res.stencil));

}


void Sys_convertViewPort(const viewport &view, D3D11_VIEWPORT &dxView) {
	dxView.TopLeftX = view.topLeftX;
	dxView.TopLeftY = view.topLeftY;
	dxView.Height = view.height;
	dxView.Width = view.width;
	dxView.MinDepth = view.minDepth;
	dxView.MaxDepth = view.maxDepth;
}

void Sys_SetandClearView(const renderView &view) {
	D3D11_VIEWPORT viewPort;
	Sys_convertViewPort(view.view,viewPort);
	win32.pContext->OMSetRenderTargets(1,&view.res.target,view.res.stencil);
	win32.pContext->RSSetViewports(1,&viewPort);
	win32.pContext->ClearRenderTargetView(view.res.target,glm::value_ptr(view.clearColor));
	win32.pContext->ClearDepthStencilView(view.res.stencil, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
}

bool Sys_CreateBuffer(Buffer* buffer,void* data) {
	D3D11_BUFFER_DESC bd;
	Sys_ConvertBufferFormat(bd,*buffer);
	if (data == NULL) {
		HR(win32.pDevice->CreateBuffer(&bd,NULL,&buffer->data.res));
		return true;
	}
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	HR(win32.pDevice->CreateBuffer(&bd,&initData,&buffer->data.res));
	return true;
}

void Sys_Log_Shader_Errors(ID3D10Blob *errors,const SiString& shaderName) {
	LogLine(shaderName + " failed to Compile",Logging::LOG_ERROR);
	char* errorMsg = static_cast<char*>(errors->GetBufferPointer());
	size_t bufSize = errors->GetBufferSize();
	LogLine(errorMsg,Logging::LOG_ERROR);
	errors->Release();
}

void Sys_Shader_SetConstBuffer(Sys_Buff_t constBuffer, const void** data,const size_t dSize,
							   const unsigned int numBuffers, const unsigned int whichBuffer) {
	for (unsigned int bufNum(0);bufNum < numBuffers;++bufNum) {
		D3D11_MAPPED_SUBRESOURCE res;
		HRESULT result = win32.pContext->Map(constBuffer.res,0,D3D11_MAP_WRITE_DISCARD,0,&res);
		if (FAILED(result)) {
			return;
		}
		memcpy(res.pData,data,dSize);
		win32.pContext->Unmap(constBuffer.res,0);
		win32.pContext->VSSetConstantBuffers(bufNum,1,&constBuffer.res);
	}
}

ID3D10Blob* Sys_Shader_Compile(const SiString& filename,const SiString& shaderFuncName,const SiString& type) {
	ID3D10Blob* shader(0);
	ID3D10Blob* errors(0);
	unsigned int flags(D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION);
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ff476261%28v=vs.85%29.aspx
	HRESULT result = D3DX11CompileFromFileA(filename.c_str(),NULL,NULL,shaderFuncName.c_str(),type.c_str(),flags,0,NULL,&shader,&errors,NULL);
	if (FAILED(result)) {
		if (errors)
			Sys_Log_Shader_Errors(errors,filename);
		else
			LogLine("Unable to find shader file: " + filename,Logging::LOG_ERROR);
		return NULL;
	}
	return shader;
}

const SiString sys_shader_typ_lt[] = {
	"ps_5_0",
	"vs_5_0"
};
const SiString& Sys_Shader_convert_type(Shader::S_Type type) {
	return sys_shader_typ_lt[type];
}

bool Sys_Shader_Create(Shader *shader,BUFFER_LAYOUT layout) {
	//Compile Shader
	ID3D10Blob* byteCode = Sys_Shader_Compile(shader->m_FileName,
		shader->m_FuncName,Sys_Shader_convert_type(shader->type));
	if (byteCode == NULL)
		return false;
	//Create Shader
	HRESULT result;
	switch (shader->type) {

		case Shader::S_VERTEX:
			result = win32.pDevice->CreateVertexShader(byteCode->GetBufferPointer(),byteCode->GetBufferSize(),NULL,&shader->vs.shader);
			break;
		case Shader::S_PIXEL:
			result = win32.pDevice->CreatePixelShader(byteCode->GetBufferPointer(),byteCode->GetBufferSize(),NULL,&shader->ps.shader);
			break;
		default:
			LogLine("Uknown shader type",Logging::LOG_ERROR);
			return false;
	}
	if (FAILED(result)) {
		LogLine("Unable to create shader " + shader->m_FileName,Logging::LOG_ERROR);
		return false;
	}
	if (shader->type == Shader::S_PIXEL)
		return true;

	D3D11_INPUT_ELEMENT_DESC layoutDesc[3];
	switch (layout) {
		case BUFFER_LAYOUT::POS_NORM_TC:
			layoutDesc[2].SemanticName = "TEXCOORD";
			layoutDesc[2].SemanticIndex = 0;
			layoutDesc[2].Format =DXGI_FORMAT_R32G32_FLOAT;
			layoutDesc[2].InputSlot = 0;
			layoutDesc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			layoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			layoutDesc[2].InstanceDataStepRate = 0;

		case BUFFER_LAYOUT::POS_NORM:
			layoutDesc[1].SemanticName = "NORMAL";
			layoutDesc[1].SemanticIndex = 0;
			layoutDesc[1].Format =DXGI_FORMAT_R32G32B32_FLOAT;
			layoutDesc[1].InputSlot = 0;
			layoutDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			layoutDesc[1].InstanceDataStepRate = 0;

		case BUFFER_LAYOUT::POS:
			layoutDesc[0].SemanticName = "POSITION";
			layoutDesc[0].SemanticIndex = 0;
			layoutDesc[0].Format =DXGI_FORMAT_R32G32B32_FLOAT;
			layoutDesc[0].InputSlot = 0;
			layoutDesc[0].AlignedByteOffset = 0;
			layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			layoutDesc[0].InstanceDataStepRate = 0;
			break;

		default:
			LogLine("invalid layout for "+ shader->m_FileName,Logging::LOG_ERROR);
			break;
	}
	HRESULT inputResult = win32.pDevice->CreateInputLayout(layoutDesc,(unsigned int)layout,byteCode->GetBufferPointer(),
		byteCode->GetBufferSize(),&shader->layout.mVertexLayout);
	if (FAILED(inputResult)) {
		LogLine("Unable to create vertex input layout",Logging::LOG_ERROR);
			return false;
	}
	byteCode->Release();
	return true;
}


void Sys_Shader_Set(Sys_VS_t &vs,Sys_Layout_t &layout,Sys_PS_t &ps) {
	win32.pContext->IASetInputLayout(layout.mVertexLayout);
	win32.pContext->PSSetShader(ps.shader,NULL,0);
	win32.pContext->VSSetShader(vs.shader,NULL,0);
}

void Sys_Draw(Buffer &verts) {
	win32.pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	unsigned int stride = verts.stride;
	unsigned int offset = 0;
	win32.pContext->IASetVertexBuffers(0,1,&verts.data.res,&stride,&offset);
	win32.pContext->Draw(verts.size,0);
}
void Sys_Draw_Indexed(Buffer &verts,Buffer &indices) {
	win32.pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	unsigned int stride = verts.stride;
	unsigned int offset = 0;
	win32.pContext->IASetVertexBuffers(0,1,&verts.data.res,&stride,&offset);
	win32.pContext->IASetIndexBuffer(indices.data.res,Sys_ConvertTextureFormat(indices.format),0);
	win32.pContext->DrawIndexed(indices.size,0,0);
}

