#include "model.h"
#include "vertexBuff.h"
#include "..\framework\resource_manager.h"
#include "..\framework\Common.h"
#include "..\framework\resource_loader.h"
extern Common* common;
bool Sys_CreateBuffer(Buffer* buffer,void* data);

bool renderModel::loadMeshRaw(void* vertexBuffer,size_t primSize,size_t length,std::vector<unsigned int>& indexBuffer,BUFFER_LAYOUT format) {
	/*
	Buffer* verts = new Buffer();
	verts->cpu_access = Buffer::NONE;
	verts->size = length;
	verts->type = Buffer::BUF_TYPE::VERTEX;
	verts->usage = Buffer::USAGE::IMMUTABLE;
	verts->stride = primSize;
	if (!Sys_CreateBuffer(verts,vertexBuffer)) {
		delete verts;
		return false;
	}
	//points = verts;

	/* Disabling Index buffers, 
	*will enable them with better support for deduplication of vertex data
	Buffer* index = new Buffer();
	index->cpu_access = Buffer::NONE;
	index->size = indexBuffer.size();
	index->type = Buffer::BUF_TYPE::INDEX;
	index->usage = Buffer::USAGE::IMMUTABLE;
	index->stride = sizeof(unsigned int);
	index->format = 3;
	if (Sys_CreateBuffer(index,&indexBuffer[0]))
		indices = index;
	*/
	return true;
}

bool renderModel::loadMaterial(const SiString& name,const SiString* textureNames,const unsigned int numTextures,
					const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
					const SiString& vertexShader_filename,const SiString& vertexShader_funcname,BUFFER_LAYOUT layout) {
	material = common->m_resources->allocateMaterial(name);
	return material->init(name,textureNames,numTextures,
		pixelShader_filename,pixelShader_funcname,
		vertexShader_filename,vertexShader_funcname,layout);
}

void renderModel::load() {
	vertex.cpu_access = Buffer::NONE;
	vertex.type = Buffer::BUF_TYPE::VERTEX;
	vertex.usage = Buffer::USAGE::IMMUTABLE;
	Resource_loader::LoadModel(fileFormat,filename,vertex,indices);
	material->load();
}
