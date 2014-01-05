#ifndef _SI_SHADER_
#define _SI_SHADER_
#include "..\framework\typedefs.h"
#include "..\Sys\sys_graphics.h"
#include "vertexBuff.h"
#include "types.h"

struct Shader {
	enum S_Type {
		S_PIXEL,
		S_VERTEX
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
	Buffer registers[2];

};


#endif