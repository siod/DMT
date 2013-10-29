

#include "entity.h"
#include "loaders\loader.h"
#include "loaders\loader_OBJ.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"
class Resource_loader {
public:
	enum R_TYPE
	{
		RESOURCE_OBJ
	};

	static entity Load(R_TYPE type, const char* filename) {
		Log("Loading resource",Logging::LOG_INFO);
		LogLine(filename,Logging::LOG_INFO);
		switch (type) {
			case RESOURCE_OBJ:
				loader_OBJ loader = loader_OBJ(filename);
				loader.load();
				if (loader.m_status == File_resource_loader::LOADED) {
					LogLine("Resource Loaded",Logging::LOG_INFO);
					loader.m_data.hidden = false;
					loader.m_data.pos = vec3(0.0,0.0,0.0);
					loader.m_data.rot = vec4(1.0,0.0,0.0,1.0);
					loader.m_data.state = entity::STATE_OK;
					return loader.m_data;
				} else {
					Log("Failed to load Resource: ",Logging::LOG_ERROR);
					LogLine(filename,Logging::LOG_ERROR);
					return entity();
				}
		}
		LogLine("Unsupported resource",Logging::LOG_ERROR);
		return entity();
	}

private:

};