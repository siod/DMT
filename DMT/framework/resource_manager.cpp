#include "resource_manager.h"
#include "resource_loader.h"
bool Sys_chdir(const char* dir);
bool Resource_manager::init() {
	if (!Sys_chdir("..\\resources")) {
		Log("unable to change into resouces folder\n",Logging::LOG_ERROR);
		return false;
	}
	return loadConfig("resources.json");
}
entity* Resource_manager::loadEntity(const char* name) {
	return addEntity("utah teapot",
				Resource_loader::Load(Resource_loader::RESOURCE_OBJ,name));
}

bool Resource_manager::loadConfig(const char* name) {
	return Resource_loader::LoadConfig(name);
}