#ifndef _ENTITY_
#define _ENTITY_
#include "..\renderer\model.h"
#include "math.h"
class entity {

public:
	enum STATE {
		STATE_ERROR,
		STATE_OK,
	};


	entity():id(0),model(NULL),state(STATE_ERROR),hidden(true),pos(0.0f,0.0f,0.0f),rot(0.0f,0.0f,0.0f,0.0f),name("") {}

	void load() {
		model->load();
	}

	guid id;
	renderModel* model;
	STATE state;
	bool	hidden;
	vec3 pos;
	vec4 rot;
	SiString name;

};
#endif