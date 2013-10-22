#include "model.h"
#include "vertexBuff.h"
#include "..\framework\resource_manager.h"
#include "..\framework\Common.h"
extern Common* common;
bool Sys_CreateBuffer(RenderBuffer* buffer,void* data);
bool renderModel::loadMesh(std::vector<vert3>& vertices,std::vector<unsigned int>& indices) {
	RenderBuffer* verts = new RenderBuffer();
	verts->cpu_writable = false;
	verts->size = vertices.size()*sizeof(vert3);
	verts->type = RenderBuffer::BUF_TYPE::VERTEX;
	verts->usage = RenderBuffer::USAGE::IMMUTABLE;
	Sys_CreateBuffer(verts,&vertices[0]);

	RenderBuffer* index = new RenderBuffer();
	verts->cpu_writable = false;
	verts->size = indices.size()*sizeof(unsigned int);
	verts->type = RenderBuffer::BUF_TYPE::INDEX;
	verts->usage = RenderBuffer::USAGE::IMMUTABLE;
	Sys_CreateBuffer(verts,&indices[0]);
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
