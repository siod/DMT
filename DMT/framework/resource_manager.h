

#include "..\renderer\TextureManager.h"
#include "..\renderer\Shader.h"
#include "..\renderer\Material.h"
#include "entity.h"
#include "level.h"

class Resource_manager {

typedef std::unordered_map<guid,Shader> shaderCache;
typedef std::unordered_map<guid,Material> materialCache;
typedef std::unordered_map<guid,renderModel> modelCache;
typedef std::unordered_map<guid,entity> entityCache;
typedef std::unordered_map<guid,Level> levelCache;
typedef std::unordered_map<SiString,guid> guidCache;
public:
	Resource_manager():textures(),shaders(),materials(),entities(),models(),guids() {}

	void init();
	entity* loadEntity(const char* name);


	guid lookupGUID(const SiString& name) {
		return guids[name];
	}

	template<typename T> static T* allocate(std::unordered_map<guid,T>& cache,
											const guid id) {
		if (cache.find(id) != cache.end()) {
			return &cache[id];
		}
		T newRes;
		newRes.id = id;
		cache[id] = newRes;
		return &cache[id];
	}

	template<typename T> T* allocate(std::unordered_map<guid,T>& cache,
											const SiString& name) {
		return allocate(cache,lookupGUID(name));
	}

	Material* allocateMaterial(const guid id) {
		return allocate(materials,id);
	}
	Shader* allocateShader(const guid id) {
		return allocate(shaders,id);
	}

	Level* allocateLevel(const guid id) {
		return allocate(levels,id);
	}

	renderModel* allocateModel(const guid id) {
		return allocate(models,id);
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

	Texture* allocateTexture(const SiString& name,Texture &newTexture) {
		textures.allocateTexture(name,newTexture);
	}

	entity* addEntity(const SiString& name,const entity & ent) {
		if (ent.state == entity::STATE_ERROR) {
			return NULL;
		}
		guid id = lookupGUID(name);
		if (entities.find(id) != entities.end()) {
			return &entities[id];
		}
		entities[id] = ent;
		return &entities[id];
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
	guidCache guids;

};