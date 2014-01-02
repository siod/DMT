
#include "loader_CONFIG.h"
#include "../resource_loader.h"
#include "../file.h"
#include "..\..\..\..\c++\SiLib\SiLog\logging.h"
#include "..\Common.h"
#include "..\resource_manager.h"
#include "..\entity.h"
extern Common* common;


void loader_CONFIG::loadVec3(vec3 &vec, configdata& vector) {
		vec.x = vector["x"].GetDouble();
		vec.y = vector["y"].GetDouble();
		vec.z = vector["z"].GetDouble();
}

void loader_CONFIG::loadVec4(vec4 &vec, configdata& vector) {
		vec.x = vector["x"].GetDouble();
		vec.y = vector["y"].GetDouble();
		vec.z = vector["z"].GetDouble();
		vec.w = vector["w"].GetDouble();
}

void loader_CONFIG::loadMaterials(configdata& materials) {

}

void loader_CONFIG::loadShaders(configdata& shaders) {

}
void loader_CONFIG::loadTextures(configdata& textures) {

}

void loader_CONFIG::loadModels(configdata& models) {

}
void loader_CONFIG::loadEntities(configdata& entities) {
	if (!entities.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < entities.Size();++i) {
		configdata& config(entities[i]);
		entity  newEntity = Resource_loader::Load(Resource_loader::getType(entities[i]["format"].GetString()),
			SiString("../resources/") + entities[i]["file"].GetString());
		loadVec3(newEntity.pos,entities[i]["pos"]);
		loadVec4(newEntity.rot,entities[i]["rot"]);
		newEntity.name = entities[i]["name"].GetString();

	}
}

void loader_CONFIG::loadLevels(configdata& levels) {
	if (!levels.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < levels.Size();++i) {
		configdata& level(levels[i]);
		Level* newLevel = common->m_resources->allocateLevel(level["name"].GetString());
		newLevel->m_id = level["guid"].GetUint64();
		newLevel->m_id = level["guid"].GetUint64();
		newLevel->friendlyName = level["friendlyName"].GetString();
		newLevel->startPos.x = level["startLoc"]["x"].GetDouble();
		newLevel->startPos.y = level["startLoc"]["y"].GetDouble();
		newLevel->startPos.z = level["startLoc"]["z"].GetDouble();
		configdata& entities(level["entities"]);
		for (rapidjson::SizeType j(0); j != levels.Size(); ++j) {
			newLevel->entites.push_back(entities[i].GetUint64());
		}
	}

}


void loader_CONFIG::load() {

	
	SiString raw(Files::slurp(m_filename));
	rapidjson::Document config;
	if (config.Parse<0>(raw.c_str()).HasParseError()) {
		m_status = FAILED;
		return;
	}
	Log("Parsed config file\n",Logging::LOG_INFO);
	if (!(config.HasMember("textures") &&
		config.HasMember("shaders") &&
		config.HasMember("materials") &&
		config.HasMember("entities") &&
		config.HasMember("levels") &&
		config.HasMember("root"))) {
			Log("malformed config file\n",Logging::LOG_ERROR);
			m_status = FAILED;
			return;
	}
	const rapidjson::Value& root(config["root"]);
	if (!root.HasMember("startLevel")) {
		Log("No start level present\n",Logging::LOG_ERROR);
		m_status = FAILED;
		return;
	}
	loadTextures(config["textures"]);
	loadShaders(config["shaders"]);
	loadMaterials(config["materials"]);
	loadModels(config["models"]);
	loadEntities(config["entities"]);
}