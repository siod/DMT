#include <D3D11.h>
#include "renderer.h"
#include "..\Sys\sys_graphics.h"
#include "Texture.h"
#include "..\framework\Common.h"
#include "..\framework\resource_manager.h"
#include "TextureManager.h"

extern Common* common;

void Renderer::init() {
	int screenWidth = 1280;
	int screenHeight = 720;
	driver_params_t params;
	params.width = screenWidth;
	params.height = screenHeight;
	params.numSamples =1;
	params.fullscreen = false;
	params.deviceFlags = 1;
	Sys_InitGraphics(params);
	renderView screen;
	screen.clearColor= vec4(1.0f,0.0f,0.0f,1.0f);
	screen.view.topLeftX = 0;
	screen.view.topLeftY = 0;
	screen.view.height = screenHeight;
	screen.view.width = screenWidth;
	screen.view.minDepth = 0.0f;
	screen.view.maxDepth = 1.0f;

	screen.stencilTexture = new Texture();
	screen.stencilTexture->format =1;
	screen.stencilTexture->mipLevels = 1;
	screen.stencilTexture->height = screenHeight;
	screen.stencilTexture->width = screenWidth;
	screen.stencilTexture->usage = 0;
	screen.stencilTexture->bindFlags = 6;
	screen.stencilTexture->cpu_writable = false;
	common->m_resources->textures.allocateTexture("stencil",*screen.stencilTexture);
	Sys_CreateScreenBuffers(screen);
	allocateView(screen);
}

void Renderer::allocateView(renderView& view) {
	m_views.push_back(view);

}

void Renderer::frame() {
	for(int i(0),count(m_views.size());i < count;++i) {
		Sys_SetandClearView(m_views[i]);
		for (int j = 0; j < m_queue.size(); ++j)
		{
			Sys_Shader_Set(m_queue[j]->model.material->m_VS->vs,m_queue[j]->model.material->m_PS->ps);
			mat4 data[3];

			data[0] = translate(mat4(1.0f),m_queue[j]->pos);
			data[1] = m_views[i].viewMat;
			data[2] = m_views[i].projection;
						
			Sys_Shader_SetConstBuffer(m_queue[j]->model.material->m_VS->registers[0],(const void**)&data,sizeof(mat4)*3,1,0);
			Sys_Draw_Indexed(*m_queue[j]->model.points,*m_queue[j]->model.indices);

		}
		Sys_SwapAndDisplay();
	}
}