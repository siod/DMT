

#include "entity.h"
#include "loaders\loader.h"
#include "loaders\loader_OBJ.h"
#include "loaders\loader_CONFIG.h"
#include "..\..\..\c++\SiLib\SiLog\logging.h"
#include "..\renderer\model.h"
#include <map>
class Resource_loader {
public:
	enum R_TYPE
	{
		RESOURCE_OBJ,
		RESOURCE_CONFIG
	};


	static R_TYPE getType(const SiString& sType) {
		return RESOURCE_OBJ;
	}

	static bool LoadModel(const renderModel::MODEL_FILE_TYPE type, const SiString& filename,Buffer& vertex,Buffer& indices) {
		Log("Loading resource",Logging::LOG_INFO);
		LogLine(filename,Logging::LOG_INFO);
		switch (type) {
			case RESOURCE_OBJ: {
				loader_OBJ loader(filename.c_str());
				loader.load(vertex,indices);
				return true;
				   }
			default:
				LogLine("Unkown resource type",Logging::LOG_ERROR);
		}
		LogLine("Unsupported resource",Logging::LOG_ERROR);
		return false;
	}


	static entity Load(R_TYPE type, const SiString& filename) {
		Log("Loading resource",Logging::LOG_INFO);
		LogLine(filename,Logging::LOG_INFO);
		switch (type) {
			case RESOURCE_OBJ: {
				/*
				loader_OBJ loader = loader_OBJ(filename.c_str());
				loader.load();
				if (loader.m_status == File_resource_loader::LOADED) {
					LogLine("Resource Loaded",Logging::LOG_INFO);
					loader.m_data.hidden = false;
					/*
					loader.m_data.pos = vec3(0.0,0.0,0.0);
					loader.m_data.rot = vec4(1.0,0.0,0.0,1.0);
					loader.m_data.state = entity::STATE_OK;
					return loader.m_data;
				} else {
					Log("Failed to load Resource: ",Logging::LOG_ERROR);
					LogLine(filename,Logging::LOG_ERROR);
					return entity();
				}
				*/
		   }
			default:
				LogLine("Unkown resource type",Logging::LOG_ERROR);
		}
		LogLine("Unsupported resource",Logging::LOG_ERROR);
		return entity();
	}

	static bool LoadConfig(const char* filename) {
		loader_CONFIG config(filename);
		config.load();
		return config.m_status == File_resource_loader::STATUS::LOADED;
	}

private:

};