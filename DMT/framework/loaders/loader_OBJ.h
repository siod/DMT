
#include "loader.h"
#include <vector>
class loader_OBJ : public File_resource_loader {
typedef  unsigned int INDEX_TYPE;
public:
	loader_OBJ(const char* filename): File_resource_loader(filename) { }
	virtual void load();
	virtual ~loader_OBJ() {}
private:
	void loader_OBJ::addVertex(std::string& input,std::vector<vec3>& vec);
	void loader_OBJ::addTexCoord(std::string& input,std::vector<vec2>& vec);
	void loader_OBJ::LightingInfo(std::string& input,size_t num,std::vector<vec3>& vec);
	void loader_OBJ::addFace(std::string& input,std::vector<INDEX_TYPE>& vindices,
		std::vector<INDEX_TYPE>& nindices,std::vector<INDEX_TYPE>& tindices);
	bool loader_OBJ::loadfile(std::vector<vec3> &verts, std::vector<vec3> &norms,
		std::vector<vec2> &texCoords, std::vector<INDEX_TYPE> &vindices,
		std::vector<INDEX_TYPE> &nindices,std::vector<INDEX_TYPE> &tindices);
};