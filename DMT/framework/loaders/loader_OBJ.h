
#include "loader.h"
#include <vector>
class loader_OBJ : public File_resource_loader {
typedef  unsigned int INDEX_TYPE;
public:
	loader_OBJ(const char* filename): File_resource_loader(filename) { }
	virtual void load(Buffer& vertex,Buffer& indices);
	virtual ~loader_OBJ() {}
private:
	void addVertex(std::string& input,std::vector<vec3>& vec);
	void addTexCoord(std::string& input,std::vector<vec2>& vec);
	void LightingInfo(std::string& input,size_t num,std::vector<vec3>& vec);
	void addFace(std::string& input,std::vector<INDEX_TYPE>& vindices,
		std::vector<INDEX_TYPE>& nindices,std::vector<INDEX_TYPE>& tindices);
	bool loadfile(std::vector<vec3> &verts, std::vector<vec3> &norms,
		std::vector<vec2> &texCoords, std::vector<INDEX_TYPE> &vindices,
		std::vector<INDEX_TYPE> &nindices,std::vector<INDEX_TYPE> &tindices);
};