#ifndef _SI_SHADER_
#define _SI_SHADER_
#include "..\framework\typedefs.h"
#include "..\Sys\sys_graphics.h"

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
	SiString m_FuncName;
	SiString m_FileName;
	S_Type type; 
	unsigned int flags;
	Sys_Buff_t registers[2];

};


#endif