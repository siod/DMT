
#ifndef _MATERIAL_
#define _MATERIAL_
#include "..\Sys\sys_graphics.h"
class Material {


private:
	Texture* textures[4];
	Shader* shaders[4];

};
#endif