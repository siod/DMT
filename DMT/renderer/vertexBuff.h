
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
	unsigned int size;
	BUF_TYPE type;
	USAGE usage;
	bool cpu_writable;

};



class vertexBuffer {




};