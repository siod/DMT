#include "resource_manager.h"
#include "resource_loader.h"
void Resource_manager::init() {

}
void Resource_manager::loadEntity(const char* name) {
	Resource_loader::Load(Resource_loader::RESOURCE_OBJ,name);
}