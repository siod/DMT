
#include <vector>
#include "..\framework\math.h"
#include "..\Sys\sys_graphics.h"
#include "Material.h"
class renderModel {
public:
	enum MODEL_STATUS {
		OK,
		FAIL,
		LOADED,
		INACTIVE
	};
	enum MODEL_FILE_TYPE {
		MODEL_OBJ
	};
	renderModel():points(),indices(),material(NULL),status(INACTIVE) {}

	void load(std::vector<vert3>&,std::vector<unsigned int>&);

private:
	struct RenderBuffer* points;
	struct RenderBuffer* indices;
	//VertBuff* normals; No vertex based normal maps
	Material* material;
	MODEL_STATUS status;

};