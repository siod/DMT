

#include "..\renderer\TextureManager.h"

class Resource_manager {

public:
	Resource_manager():textures() {}

	void init();
	void loadEntity(const char* name);

private:
	TextureManager textures;

};