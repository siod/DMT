
#ifndef _SI_RENDERBUFFER_
#define _SI_RENDERBUFFER_
Sys_Layout_t;
Sys_Buff_t;
struct Buffer {
	enum BUF_TYPE {
		VERTEX,
		INDEX,
		CONSTANT,
		RESOURCE,
		STREAM,
		RENDER_TARGET,
		DEPTH_STENCIL,
		INVALID
	};
	enum USAGE {
		DEFAULT,
		IMMUTABLE,
		DYNAMIC,
		STAGING,
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

	static BUF_TYPE StringToType(const SiString& type) {
		switch (type[0]) {
			case 'v':
				return BUF_TYPE::VERTEX;
			case 'i':
				return BUF_TYPE::INDEX;
			case 'c':
				return BUF_TYPE::CONSTANT;
			case 'r':
				if (type[2] == 's') {
					return BUF_TYPE::RESOURCE;
				} else {
					return BUF_TYPE::RENDER_TARGET;
				}
			case 's':
				return BUF_TYPE::STREAM;
			case 'd':
				return BUF_TYPE::DEPTH_STENCIL;
			default:
				return BUF_TYPE::INVALID;
		}
	}

	static USAGE StringToUsage(const SiString&& type) {
		switch (type[0]) {
			case 'd':
				if (type[1] == 'e') {
					return USAGE::DEFAULT;
				} else {
					return USAGE::DYNAMIC;
				}
			case 'i':
				return USAGE::IMMUTABLE;
			case 's':
				return USAGE::STAGING;
			default:
				return USAGE::DEFAULT;
		}
	}

	static CPU_ACCESS StringToAccess(const SiString&& type) {
		switch (type[0]) {
			case 'n':
				return CPU_ACCESS::NONE;
			case 'w':
				return CPU_ACCESS::WRITE;
			case 'r':
				return CPU_ACCESS::READ;
			default:
				return CPU_ACCESS::NONE;
		}
	}





};
#endif
