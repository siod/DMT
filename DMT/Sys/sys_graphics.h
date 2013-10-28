
#ifndef _SYS_GRAPHICS_
#define _SYS_GRAPHICS_
#include "..\framework\typedefs.h"
#include "..\renderer\types.h"
#include <D3D11.h>
typedef struct {
	int width;
	int height;
	int numSamples;
	unsigned int deviceFlags;
	bool fullscreen;
} driver_params_t;

typedef struct {
	int byteWidth;
	int accessable;
} buffer_params_t;

typedef struct {

} texture_params_t;

struct ID3D11ShaderResourceView;

typedef struct {
	//
	//ID3D11ShaderResourceView* res;
	ID3D11Texture2D* res;
} Sys_texture_t; 

struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct D3D11_VIEWPORT;
typedef struct {
	ID3D11RenderTargetView* target;
	ID3D11DepthStencilView* stencil;
} Sys_renderTarget_t;

struct ID3D11Buffer;
struct ID3D11InputLayout;

typedef struct win_Layout_s {
	ID3D11InputLayout*	mVertexLayout;
} Sys_Layout_t;

typedef struct win_Buff_s {
	ID3D11Buffer* res;
} Sys_Buff_t;


struct ID3D11EffectTechnique;
typedef struct {
	ID3D11VertexShader* shader;
} Sys_VS_t;

typedef struct {
	ID3D11PixelShader* shader;
} Sys_PS_t;

typedef struct {
	ID3D10Blob* blob;
} Sys_Blob_t;

struct renderView;
void Sys_InitWindow();
void Sys_InitGraphics(driver_params_t);
void Sys_ShutdownGraphics();
void Sys_SwapAndDisplay();
void Sys_SetandClearView(const renderView &view);
//bool Sys_CreateTexture();
extern struct Texture;
void Sys_ConvertTextureFormat(D3D11_TEXTURE2D_DESC &desc,const Texture& engineDesc);
void Sys_CreateTexture(Texture &texture);
void Sys_LoadTextureFromFile(Texture &texture,const SiString& filename);
Sys_texture_t Sys_LoadTexture();
struct Buffer;
bool Sys_CreateBuffer(Buffer* buffer,void* data);

void Sys_CreateScreenBuffers(renderView &view);

void Sys_ReleaseTexture(Sys_texture_t& texture);
extern struct Shader;
void Sys_Shader_SetConstBuffer(Sys_Buff_t constBuffer, const void** data,const size_t dSize,
							   const unsigned int numBuffers, const unsigned int whichBuffer);
bool Sys_Shader_Create(Shader *shader,BUFFER_LAYOUT layout);
void Sys_Shader_Set(Sys_VS_t &vs,Sys_Layout_t &layout,Sys_PS_t &ps);
void Sys_Draw_Indexed(Buffer &verts,Buffer &indices);
void Sys_Draw(Buffer &verts);
#endif