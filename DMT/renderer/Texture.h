
#ifndef _TEXTURE_
#define _TEXTURE_
#include "..\Sys\sys_graphics.h"
struct sampling_info {
	unsigned int num;
	unsigned int quality;
};

struct Texture {
	Sys_texture_t texture;
	unsigned int width;
	unsigned int height;
	unsigned int mipLevels;
	unsigned int format;
	unsigned int usage;
	unsigned int bindFlags;
	sampling_info sampling;
	bool cpu_writable;
};
#endif