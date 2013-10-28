
#ifndef _MATERIAL_
#define _MATERIAL_
#include "..\Sys\sys_graphics.h"
#include "Shader.h"
class Material {

	Material(const SiString& name,const SiString* textureNames,const unsigned int numTextures,
		const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
		const SiString& vertexShader_filename,const SiString& vertexShader_funcname)
		:m_name(name), m_texName(), 
		m_textures(), m_PS(NULL), m_VS(NULL),  m_numTextures(numTextures) {
			for (int i(0); i < numTextures;++i) {
				m_texName[i] = textureNames[i];
			}
	}

public:
	Material() :m_name(), m_texName(), 
		m_textures(), m_PS(NULL), m_VS(NULL),  m_numTextures(0) {}



	void init( const SiString& name,const SiString* textureNames,const unsigned int numTextures,
		const SiString& pixelShader_filename, const SiString& pixelShader_funcname, 
		const SiString& vertexShader_filename,const SiString& vertexShader_funcname,BUFFER_LAYOUT layout);

//private:
	SiString m_name;
	SiString m_texName[4];
	Texture* m_textures[4];
	Shader* m_PS;
	Shader* m_VS;
	unsigned int m_numTextures;

};
#endif