#ifndef _LOADER_CONFIG_
#define _LOADER_CONFIG_
#include "loader.h"
#include <vector>
#include "../../lib/rapidjson/include/rapidjson/document.h"
typedef  rapidjson::Value configdata;
class loader_CONFIG : public File_resource_loader {
typedef  unsigned int INDEX_TYPE;
public:
	guid startid;
	loader_CONFIG(const char* filename): File_resource_loader(filename) { }
	virtual void load();
	virtual ~loader_CONFIG() {}
private:

	void loadMaterials(configdata& materials) ;

	void loadModels(configdata& models);

	void loadEntities(configdata& entities);

	void loadShaders(configdata& shaders) ;
	
	void loadTextures(configdata& textures) ;

	void loadLevels(configdata& levels) ;

	inline void loader_CONFIG::loadVec3(vec3 &vec, configdata& vector);
	inline void loader_CONFIG::loadVec4(vec4 &vec, configdata& vector);
	inline void loader_CONFIG::loadBuffer(Buffer &buff,configdata& buffer);
};

#endif