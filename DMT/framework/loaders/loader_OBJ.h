
#include "loader.h"
#include <vector>
class loader_OBJ : File_resource_loader {
public:
	loader_OBJ(const char* filename): File_resource_loader(filename) { }
	virtual void load();
private:
	void loader_OBJ::addVertex(std::string& input,std::vector<vert3>& vec);
	void loader_OBJ::LightingInfo(std::string& input,size_t num,std::vector<vert3>& vec);
	void loader_OBJ::addFace(std::string& input,std::vector<unsigned int>& indices);
	bool loader_OBJ::loadfile(std::vector<vert3> &verts, std::vector<unsigned int> &indices);
};