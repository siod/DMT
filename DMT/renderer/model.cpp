#include "model.h"
#include "vertexBuff.h"
#include "..\framework\resource_manager.h"
#include "..\framework\Common.h"
extern Common* common;
bool Sys_CreateBuffer(Buffer* buffer,void* data);
bool renderModel::loadMesh(std::vector<vec3>& vertexBuffer,std::vector<unsigned int>& indexBuffer) {
	Buffer* verts = new Buffer();
	verts->cpu_access = Buffer::NONE;
	verts->size = vertexBuffer.size();
	verts->type = Buffer::BUF_TYPE::VERTEX;
	verts->usage = Buffer::USAGE::IMMUTABLE;
	verts->stride = sizeof(vec3);
	//verts->stride = sizeof(float);
	if (Sys_CreateBuffer(verts,&vertexBuffer[0]))
		points = verts;

	Buffer* index = new Buffer();
	index->cpu_access = Buffer::NONE;
	index->size = indexBuffer.size();
	index->type = Buffer::BUF_TYPE::INDEX;
	index->usage = Buffer::USAGE::IMMUTABLE;
	index->stride = sizeof(unsigned int);
	index->format = 3;
	if (Sys_CreateBuffer(index,&indexBuffer[0]))
		indices = index;
	return true;

}

bool renderModel::loadMaterial(const SiString& name,const SiString* textureNames,const unsigned int numTextures,
					const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
					const SiString& vertexShader_filename,const SiString& vertexShader_funcname) {
	material = common->m_resources->allocateMaterial(name);
	material->init(name,textureNames,numTextures,
		pixelShader_filename,pixelShader_funcname,
		vertexShader_filename,vertexShader_funcname);
	return true;
}
