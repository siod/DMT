#ifndef _SI_SHADER_
#define _SI_SHADER_
#include "..\framework\typedefs.h"
#include "..\Sys\sys_graphics.h"
#include "vertexBuff.h"
#include "types.h"

struct Shader {
	enum S_Type {
		PIXEL,
		VERTEX,
		INVALID
	};
	union
	{
		Sys_PS_t ps;
		Sys_VS_t vs;
	};
	guid id;
	SiString name; 
	Sys_Layout_t layout;
	BUFFER_LAYOUT m_layout;
	SiString m_FuncName;
	SiString m_FileName;
	S_Type type; 
	unsigned int flags;
	unsigned int m_numRegisters;
	Buffer registers[2];
	bool loaded;

	void load() {
		if (loaded)
			return;
		if (!Sys_Shader_Create(this,m_layout))
			return;
		for (size_t i(0); i != m_numRegisters; ++i) {
			Sys_CreateBuffer(&registers[i],NULL);
		}
		loaded = true;
	}

	void unload() {


	}
	static S_Type StringToType(const SiString&& type) {
		switch (type[0]) {
		case 'p':
			return S_Type::PIXEL;
		case 'v':
			return S_Type::VERTEX;
		default:
			return S_Type::INVALID;
		}
	}
};


#endif