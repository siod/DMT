#include "model.h"
#include "vertexBuff.h"
bool Sys_CreateBuffer(RenderBuffer* buffer,void* data);
void renderModel::load(std::vector<vert3>& vertices,std::vector<unsigned int>& indices) {
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

}
