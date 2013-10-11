#ifndef _RENDER_VIEW_
#define _RENDER_VIEW_
#include "..\framework\math.h"
#include "..\Sys\sys_graphics.h"
struct viewport {
	float topLeftX;
	float topLeftY;
	float width;
	float height;
	float minDepth;
	float maxDepth;
};
struct renderView {
	vert4 origin;
	vert4 clearColor;
	mat4 projection;
	viewport view; 
	//Texture* viewTexture;
	Texture* stencilTexture;
	Sys_renderTarget_t res;
};

#endif