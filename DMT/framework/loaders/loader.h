
#include "..\entity.h"
class File_resource_loader {
public:
	const SiString m_filename;
	entity m_data;
	int m_status;
	File_resource_loader(const char* filename):m_filename(filename),m_data(),m_status(2) {}
	virtual void load();
	virtual ~File_resource_loader();

};