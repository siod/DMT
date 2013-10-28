
#ifndef _SI_RENDERMODEL_
#define _SI_RENDERMODEL_
#include <vector>
#include "..\framework\math.h"
#include "Material.h"
extern struct Buffer;
class renderModel {
public:
	enum MODEL_STATUS {
		OK,
		FAIL,
		LOADED,
		INACTIVE
	};
	enum MODEL_FILE_TYPE {
		MODEL_OBJ
	};
	renderModel():points(),indices(),material(NULL),status(INACTIVE) {}

	bool loadMesh(std::vector<vec3>&,std::vector<unsigned int>&);
	bool loadMaterial(const SiString& name,const SiString* textureNames,const unsigned int numTextures,
		const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
		const SiString& vertexShader_filename,const SiString& vertexShader_funcname);

	struct Buffer* points;
	struct Buffer* indices;
	//VertBuff* normals; No vertex based normal maps
	Material* material;
	MODEL_STATUS status;

};
#endif