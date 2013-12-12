
#ifndef _SI_RENDERMODEL_
#define _SI_RENDERMODEL_
#include <vector>
#include "..\framework\math.h"
#include "Material.h"
#include "types.h"
struct Buffer;
class renderModel {
	bool renderModel::loadMeshRaw(void* vertexBuffer,size_t primSize,size_t length,std::vector<unsigned int>& indexBuffer,BUFFER_LAYOUT format);
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

	template<typename T>
	bool loadMesh(std::vector<T>& verts,std::vector<unsigned int>&indices,BUFFER_LAYOUT format) {
		return loadMeshRaw(&verts[0],sizeof(T),verts.size(),indices,format);
	}

	bool loadMaterial(const SiString& name,const SiString* textureNames,const unsigned int numTextures,
		const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
		const SiString& vertexShader_filename,const SiString& vertexShader_funcname,BUFFER_LAYOUT layout);

	struct Buffer* points;
	struct Buffer* indices;
	//VertBuff* normals; No vertex based normal maps
	Material* material;
	MODEL_STATUS status;

};
#endif