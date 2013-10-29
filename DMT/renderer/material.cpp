#include "Material.h"
#include "..\Sys\sys_graphics.h"
#include "..\framework\Common.h"
#include "..\framework\resource_manager.h"
#include "vertexBuff.h"
extern Common* common;

bool Material::init( const SiString& name,const SiString* textureNames,const unsigned int numTextures,
					const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
					const SiString& vertexShader_filename,const SiString& vertexShader_funcname,BUFFER_LAYOUT layout) {
	m_numTextures = numTextures;
	m_name = name;
	for (int i = 0; i < numTextures; i++) {
		m_texName[i] = textureNames[i];
	}
	m_PS = common->m_resources->allocateShader(pixelShader_filename);
	m_PS->m_FileName = pixelShader_filename;
	m_PS->m_FuncName = pixelShader_funcname;
	m_PS->type = Shader::S_PIXEL;
	if (!Sys_Shader_Create(m_PS,BUFFER_LAYOUT::NONE)) {
		return false;
	}

	m_VS = common->m_resources->allocateShader(vertexShader_filename);
	m_VS->m_FileName = vertexShader_filename;
	m_VS->m_FuncName = vertexShader_funcname;
	m_VS->type = Shader::S_VERTEX;
	if (!Sys_Shader_Create(m_VS,layout)) {
		return false;
	}

	m_VS->registers[0].usage = Buffer::DYNAMIC;
	m_VS->registers[0].type = Buffer::CONSTANT;
	m_VS->registers[0].size = sizeof(mat4)*3;
	m_VS->registers[0].cpu_access = Buffer::WRITE;
	//0 is allowed for unstructured data
	m_VS->registers[0].stride = 0;
	Sys_CreateBuffer(&m_VS->registers[0],NULL);
	return true;
}
/*
void Material::create() {



}
*/