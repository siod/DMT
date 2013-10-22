#include "Material.h"
#include "..\Sys\sys_graphics.h"
#include "..\framework\Common.h"
#include "..\framework\resource_manager.h"
extern Common* common;

void Material::init( const SiString& name,const SiString* textureNames,const unsigned int numTextures,
					const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
					const SiString& vertexShader_filename,const SiString& vertexShader_funcname) {
	m_numTextures = numTextures;
	m_name = name;
	for (int i = 0; i < numTextures; i++) {
		m_texName[i] = textureNames[i];
	}
	m_PS = common->m_resources->allocateShader(pixelShader_filename);
	m_PS->m_FileName = pixelShader_filename;
	m_PS->m_FuncName = pixelShader_funcname;
	m_PS->type = Shader::S_PIXEL;
	Sys_Shader_Create(m_PS);
	m_VS = common->m_resources->allocateShader(vertexShader_filename);
	m_VS->m_FileName = vertexShader_filename;
	m_VS->m_FuncName = vertexShader_funcname;
	m_VS->type = Shader::S_VERTEX;
	Sys_Shader_Create(m_VS);
}
/*
void Material::create() {



}
*/