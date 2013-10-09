
#ifndef _SYS_GRAPHICS_
#define _SYS_GRAPHICS_
#include "..\framework\typedefs.h"
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
	ID3D11ShaderResourceView* res;
} Texture; 

   struct ID3D11RenderTargetView;
   struct ID3D11DepthStencilView;
   struct D3D11_VIEWPORT;
typedef struct {
   ID3D11RenderTargetView* target;
   ID3D11DepthStencilView* stencil;
   D3D11_VIEWPORT viewPort;

} RenderTarget;

struct ID3D11Buffer;
struct ID3D11InputLayout;

typedef struct win_vertBuff_s {
	ID3D11Buffer* res;
	ID3D11InputLayout*	mVertexLayout;
} Sys_vertBuff_t;

struct ID3D11EffectTechnique;
typedef struct {
	ID3D11EffectTechnique* res;
} Shader;

struct renderView;
void Sys_InitWindow();
void Sys_InitGraphics(driver_params_t);
void Sys_ShutdownGraphics();
void Sys_SwapAndDisplay();
void Sys_SetandClearView(const renderView* view);
//bool Sys_CreateTexture();
Texture Sys_LoadTextureFromFile(const SiString&,int);
Texture Sys_LoadTexture();
struct RenderBuffer;
bool Sys_CreateBuffer(RenderBuffer* buffer,void* data);



void Sys_ReleaseTexture(Texture& texture);
#endif