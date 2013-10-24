#include "resource_manager.h"
#include "resource_loader.h"
void Resource_manager::init() {

}
entity* Resource_manager::loadEntity(const char* name) {
	return addEntity("utah teapot",Resource_loader::Load(Resource_loader::RESOURCE_OBJ,name));
}