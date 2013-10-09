#include <D3D11.h>
#include "renderer.h"
#include "..\Sys\sys_graphics.h"


void Renderer::init() {
	driver_params_t params;
	params.width = 1280;
	params.height = 720;
	params.numSamples =1;
	params.fullscreen = false;
	Sys_InitGraphics(params);
}

bool Renderer::allocateView(renderView& view) {
	return false;

}
void Renderer::frame() {



}