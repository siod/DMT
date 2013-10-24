
extern Sys_vertBuff_t;
struct RenderBuffer {
	enum BUF_TYPE {
		VERTEX,
		INDEX,
		CONSTANT
	};
	enum USAGE {
		DEFAULT,
		IMMUTABLE,
		DYNAMIC,
		STAGING
	};
	Sys_vertBuff_t data;
	BUF_TYPE type;
	USAGE usage;
	unsigned int size;
	unsigned int stride;
	unsigned int format;
	bool cpu_writable;

};

