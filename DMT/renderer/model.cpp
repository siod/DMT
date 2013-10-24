#include "model.h"
#include "vertexBuff.h"
#include "..\framework\resource_manager.h"
#include "..\framework\Common.h"
extern Common* common;
bool Sys_CreateBuffer(RenderBuffer* buffer,void* data);
bool renderModel::loadMesh(std::vector<vec3>& vertexBuffer,std::vector<unsigned int>& indexBuffer) {
	RenderBuffer* verts = new RenderBuffer();
	verts->cpu_writable = false;
	verts->size = vertexBuffer.size()*sizeof(vec3);
	verts->type = RenderBuffer::BUF_TYPE::VERTEX;
	verts->usage = RenderBuffer::USAGE::IMMUTABLE;
	verts->stride = sizeof(vec3);
	if (Sys_CreateBuffer(verts,&vertexBuffer[0]))
		points = verts;

	RenderBuffer* index = new RenderBuffer();
	index->cpu_writable = false;
	index->size = indexBuffer.size()*sizeof(unsigned int);
	index->type = RenderBuffer::BUF_TYPE::INDEX;
	index->usage = RenderBuffer::USAGE::IMMUTABLE;
	index->stride = sizeof(unsigned int);
	index->format = 3;
	if (Sys_CreateBuffer(verts,&indexBuffer[0]))
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
