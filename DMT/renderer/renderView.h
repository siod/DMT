#ifndef _RENDER_VIEW_
#define _RENDER_VIEW_
#include "..\framework\math.h"
#include "..\Sys\sys_graphics.h"
struct renderView {
	vert4 origin;
	mat4 projection;
	vert4 clearColor;
	RenderTarget res;
};

#endif