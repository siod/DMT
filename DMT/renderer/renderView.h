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
	vec4 origin;
	vec4 clearColor;
	mat4 projection;
	mat4 viewMat;
	viewport view; 
	//Texture* viewTexture;
	Texture* stencilTexture;
	Sys_renderTarget_t res;
};

#endif