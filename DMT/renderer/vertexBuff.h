
#ifndef _SI_RENDERBUFFER_
#define _SI_RENDERBUFFER_
extern Sys_Layout_t;
extern Sys_Buff_t;
struct Buffer {
	enum BUF_TYPE {
		VERTEX,
		INDEX,
		CONSTANT,
		RESOURCE,
		STREAM,
		RENDER_TARGET,
		DEPTH_STENCIL
	};
	enum USAGE {
		DEFAULT,
		IMMUTABLE,
		DYNAMIC,
		STAGING
	};
	enum CPU_ACCESS {
		NONE,
		READ,
		WRITE
	};
	Sys_Buff_t data;
	Sys_Layout_t layout;
	BUF_TYPE type;
	USAGE usage;
	unsigned int size;
	unsigned int stride;
	unsigned int format;
	CPU_ACCESS cpu_access;

};
#endif
