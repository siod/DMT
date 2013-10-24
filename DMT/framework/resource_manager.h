

#include "..\renderer\TextureManager.h"
#include "..\renderer\Shader.h"
#include "..\renderer\Material.h"
#include "entity.h"

class Resource_manager {

typedef std::unordered_map<SiString,Shader> shaderCache;
typedef std::unordered_map<SiString,Material> materialCache;
typedef std::unordered_map<SiString,entity> enityCache;
public:
	Resource_manager():textures(),shaders(),materials(),entities() {}

	void init();
	entity* loadEntity(const char* name);

	void allocateTexture(const SiString& name,Texture &newTexture) {
		textures.allocateTexture(name,newTexture);
	}

	Material* allocateMaterial(const SiString& name) {
		if (materials.find(name) != materials.end()) {
			return &materials[name];
		}
		Material newMaterial;
		materials[name] = newMaterial;
		return &materials[name];
	}
	Shader* allocateShader(const SiString& name) {
		if (shaders.find(name) != shaders.end()) {
			return &shaders[name];
		}
		Shader newShader;
		shaders[name] = newShader;
		return &shaders[name];
	}

	entity* addEntity(const SiString& name,const entity & ent) {
		if (entities.find(name) != entities.end()) {
			return &entities[name];
		}
		entities[name] = ent;
		return &entities[name];
	}


	/*
	Texture* loadTextureFromFile(const SiString& name,const int format) {
		return textures.loadTextureFromFile(name,format);
	}
	*/

	void unloadTexture(const SiString& name) {
		textures.unloadTexture(name);
	}

	TextureManager textures;
	shaderCache shaders;
	materialCache materials;
	enityCache entities;

};