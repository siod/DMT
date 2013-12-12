
#include "loader_CONFIG.h"
#include "../file.h"
#include "..\..\..\..\c++\SiLib\SiLog\logging.h"

void loader_CONFIG::loadMaterials(configdata& materials) {

}

void loader_CONFIG::loadEntities(configdata& entities) {

}
void loader_CONFIG::loadShaders(configdata& shaders) {

}
void loader_CONFIG::loadTextures(configdata& textures) {

}
void loader_CONFIG::loadLevels(configdata& levels) {

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
	loadEntities(config["entities"]);
}