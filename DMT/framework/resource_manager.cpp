#include "resource_manager.h"
#include "resource_loader.h"
bool Resource_manager::init() {
	return loadConfig("resources.json");
}
entity* Resource_manager::loadEntity(const char* name) {
	return addEntity("utah teapot",
				Resource_loader::Load(Resource_loader::RESOURCE_OBJ,name));
}

bool Resource_manager::loadConfig(const char* name) {
	return Resource_loader::LoadConfig(name);
}