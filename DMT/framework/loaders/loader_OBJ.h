
#include "loader.h"
#include <vector>
class loader_OBJ : public File_resource_loader {
public:
	loader_OBJ(const char* filename): File_resource_loader(filename) { }
	virtual void load();
	virtual ~loader_OBJ() {}
private:
	void loader_OBJ::addVertex(std::string& input,std::vector<vert3>& vec);
	void loader_OBJ::LightingInfo(std::string& input,size_t num,std::vector<vert3>& vec);
	void loader_OBJ::addFace(std::string& input,std::vector<unsigned int>& indices);
	bool loader_OBJ::loadfile(std::vector<vert3> &verts,std::vector<vert3> &norms, std::vector<unsigned int> &indices);
};