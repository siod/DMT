

#include "..\renderer\TextureManager.h"
#include "..\renderer\Shader.h"
#include "..\renderer\Material.h"
#include "entity.h"
#include "level.h"

class Resource_manager {

typedef std::unordered_map<SiString,Shader> shaderCache;
typedef std::unordered_map<SiString,Material> materialCache;
typedef std::unordered_map<SiString,renderModel> modelCache;
typedef std::unordered_map<SiString,entity> entityCache;
typedef std::unordered_map<SiString,Level> levelCache;
public:
	Resource_manager():textures(),shaders(),materials(),entities(),models() {}

	void init();
	entity* loadEntity(const char* name);

	void allocateTexture(const SiString& name,Texture &newTexture) {
		textures.allocateTexture(name,newTexture);
	}

	template<typename T> static T* allocate(std::unordered_map<SiString,T>& cache,
											const SiString& name) {
		if (cache.find(name) != cache.end()) {
			return &cache[name];
		}
		T newRes;
		cache[name] = newRes;
		return &cache[name];
	}

	Material* allocateMaterial(const SiString& name) {
		return allocate(materials,name);
	}
	Shader* allocateShader(const SiString& name) {
		return allocate(shaders,name);
	}

	Level* allocateLevel(const SiString& name) {
		return allocate(levels,name);
	}

	renderModel* allocateModel(const SiString& name) {
		return allocate(models,name);
	}

	entity* addEntity(const SiString& name,const entity & ent) {
		if (ent.state == entity::STATE_ERROR) {
			return NULL;
		}
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
	entityCache entities;
	levelCache levels;
	modelCache models;

};