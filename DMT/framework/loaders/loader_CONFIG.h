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

	void loadEntities(configdata& entities);

	void loadShaders(configdata& shaders) ;
	
	void loadTextures(configdata& textures) ;

	void loadLevels(configdata& levels) ;

};
