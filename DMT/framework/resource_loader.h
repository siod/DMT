

#include "entity.h"
#include "loaders\loader.h"
class Resource_loader {
public:
	enum R_TYPE
	{
		RESOURCE_OBJ
	};

	static entity Load(R_TYPE type, const char* filename) {
		return entity();
	}

private:

};