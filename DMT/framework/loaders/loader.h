
#ifndef _F_LOADER_
#define _F_LOADER_
#include "..\entity.h"
class File_resource_loader {
public:
	enum STATUS {
		UNLOADED,
		LOADED,
		FAILED 
	};
	const SiString m_filename;
	STATUS m_status;
	File_resource_loader(const char* filename):m_filename(filename),m_status(UNLOADED) {}
	virtual void load() {}
	virtual ~File_resource_loader() {}

};
#endif