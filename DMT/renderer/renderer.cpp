#include <D3D11.h>
#include "renderer.h"
#include "..\Sys\sys_graphics.h"
#include "Texture.h"
#include "..\framework\Common.h"
#include "..\framework\resource_manager.h"
#include "TextureManager.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"

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
	screen.clearColor= vec4(0.0f,0.0f,0.0f,1.0f);
	screen.view.topLeftX = 0;
	screen.view.topLeftY = 0;
	screen.view.height = screenHeight;
	screen.view.width = screenWidth;
	float aspect = float(screenWidth)/screenHeight;
	screen.view.minDepth = 0.0f;
	screen.view.maxDepth = 1.0f;
	screen.origin = vec3(0.0f,0.0f,10.0f);
	const mat4 dx(	1,0,0,0,
					0,1,0,0,
					0,0,2,0,
					0,0,-1,1);
	screen.projection = (perspective(60.0f,aspect,1.0f,100.0f));
	screen.viewMat = (glm::lookAt(vec3(0,0,10),vec3(0,0,0),vec3(0.0f,1.0f,0.0f)));

	screen.stencilTexture = new Texture();
	screen.stencilTexture->format =1;
	screen.stencilTexture->mipLevels = 1;
	screen.stencilTexture->height = screenHeight;
	screen.stencilTexture->width = screenWidth;
	screen.stencilTexture->usage = 0;
	screen.stencilTexture->bindFlags = 6;
	screen.stencilTexture->cpu_writable = false;
	//FIX
	common->m_resources->textures.allocateTexture("stencil",*screen.stencilTexture);
	Sys_CreateScreenBuffers(screen);
	allocateView(screen);
}

void Renderer::allocateView(renderView& view) {
	m_views.push_back(view);

}

void Renderer::frame() {
	//LogLine("drawing frame",Logging::LOG_DEBUG);
	const mat4 ident(.5,0,0,0,
					0,.5,0,0,
					0,0,.5,-10,
					0,0,0,.5);
	for(int i(0),count(m_views.size());i < count;++i) {
		Sys_SetandClearView(m_views[i]);
		for (int j = 0; j < m_queue.size(); ++j)
		{
			Sys_Shader_Set(m_queue[j]->model.material->m_VS->vs,m_queue[j]->model.material->m_VS->layout,m_queue[j]->model.material->m_PS->ps);
			mat4 data[3];

			//data[0] = glm::transpose(translate(ident,m_queue[j]->pos));
			data[0] = ident;
			data[1] = (m_views[i].viewMat);
			data[2] = (m_views[i].projection);
						
			Sys_Shader_SetConstBuffer(m_queue[j]->model.material->m_VS->registers[0].data,(const void**)glm::value_ptr(data[0]),sizeof(mat4)*3,1,0);
			Sys_Draw_Indexed(*m_queue[j]->model.points,*m_queue[j]->model.indices);

		}
		Sys_SwapAndDisplay();
	}
}