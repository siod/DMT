
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

void loader_CONFIG::loadBuffer(Buffer &buff,configdata& config) {
	buff.cpu_access = Buffer::StringToAccess(config["cpu_access"].GetString());
	buff.usage = Buffer::StringToUsage(config["usage"].GetString());
	buff.type = Buffer::StringToType(config["type"].GetString());
	//Making this constant for now
	buff.size = sizeof(mat4)*3;
	buff.stride = config["stride"].GetUint();


}

void loader_CONFIG::loadMaterials(configdata& materials) {
	if (!materials.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < materials.Size();++i) {
		configdata& config(materials[i]);
		Material* material = common->m_resources->allocateMaterial(config["guid"].GetUint64());
		material->m_name = config["name"].GetString();
		material->m_VS = common->m_resources->allocateShader(config["vertexShader"].GetUint64());
		material->m_PS = common->m_resources->allocateShader(config["pixelShader"].GetUint64());
		configdata& textures(config["textures"]);
		material->m_numTextures = textures.Size();
		for (rapidjson::SizeType j(0); j != material->m_numTextures; ++j) {
			material->m_textures[i] = common->m_resources->allocateTexture(textures[i].GetUint64());
		}

	}
}

void loader_CONFIG::loadShaders(configdata& shaders) {
	if (!shaders.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < shaders.Size();++i) {
		configdata& config(shaders[i]);
		Shader* shader = common->m_resources->allocateShader(config["guid"].GetUint64());
		shader->name = config["name"].GetString();
		shader->m_FileName = config["filename"].GetString();
		shader->m_FuncName = config["functionName"].GetString();
		shader->type = Shader::StringToType(config["type"].GetString());
		shader->m_layout = StringToBUFFER_LAYOUT(config["layout"].GetString());
		if (config.HasMember("registers") && config["registers"].IsArray()) {
			configdata& sRegisters(config["registers"]);
			shader->m_numRegisters = sRegisters.Size();
			for (rapidjson::SizeType j(0);j < shader->m_numRegisters;++j) {
				loadBuffer(shader->registers[j],sRegisters[i]);
			}
		}
	}
}
void loader_CONFIG::loadTextures(configdata& textures) {
	if (!textures.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < textures.Size();++i) {
		configdata& config(textures[i]);
		Texture* texture = common->m_resources->allocateTexture(config["guid"].GetUint64());
		texture->name = config["name"].GetString();
		texture->filename = config["filename"].GetString();
		if (config.HasMember("registername") && config["registername"].GetBool()) {
			common->m_resources->addGUIDLookup(texture->name,texture->id);
		}
	}

}

void loader_CONFIG::loadModels(configdata& models) {
	if (!models.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < models.Size();++i) {
		configdata& config(models[i]);
		renderModel* model = common->m_resources->allocateModel(config["guid"].GetUint64());
		model->filename = config["file"].GetString();
		model->name = config["name"].GetString();
		model->fileFormat = renderModel::convertToFType(config["fileformat"].GetString());
		configdata& materials(config["materials"]);
		for (rapidjson::SizeType j(0); j != materials.Size(); ++j) {
			model->material = common->m_resources->allocateMaterial(materials[i].GetUint64());
		}
	}

}
void loader_CONFIG::loadEntities(configdata& entities) {
	if (!entities.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < entities.Size();++i) {
		configdata& config(entities[i]);
		entity* newEntity = common->m_resources->allocateEntity(config["guid"].GetUint64());
		loadVec3(newEntity->pos,config["pos"]);
		loadVec4(newEntity->rot,config["rot"]);
		newEntity->name = config["name"].GetString();
		newEntity->hidden = config["hidden"].GetBool();
		newEntity->model = common->m_resources->allocateModel(config["model"].GetUint64());
	}
}

void loader_CONFIG::loadLevels(configdata& levels) {
	if (!levels.IsArray()) {
		return;
	}
	for (rapidjson::SizeType i(0);i < levels.Size();++i) {
		configdata& level(levels[i]);
		Level* newLevel = common->m_resources->allocateLevel(level["guid"].GetUint64());
		newLevel->name = level["name"].GetString();
		newLevel->friendlyName = level["friendlyName"].GetString();
		loadVec3(newLevel->startPos,level["startLoc"]);
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
		Log("json parse error\n",Logging::LOG_ERROR);
		m_status = FAILED;
		return;
	}
	Log("Parsed config file\n",Logging::LOG_INFO);
	const char* members[] = { "textures",
							"shaders",
							"materials",
							"entities",
							"levels",
							"models",
							"root" };

	for (int i(0);i != 7; ++i) {
		if (!config.HasMember(members[i])) {
			Log("malformed config file, ",Logging::LOG_ERROR);
			Log(members[i],Logging::LOG_ERROR);
			Log(" is missing\n",Logging::LOG_ERROR);
			m_status = FAILED;
			return;
		}
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
	loadLevels(config["levels"]);
	common->startLevelID = root["startLevel"].GetUint64();
	Log("Loading finished!\n",Logging::LOG_INFO);
	m_status = LOADED;

}