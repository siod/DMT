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


	entity():model(),state(STATE_ERROR),hidden(true),pos(0.0f,0.0f,0.0f),rot(0.0f,0.0f,0.0f,0.0f) {}


	renderModel model;
	STATE state;
	bool	hidden;
	vec3 pos;
	vec4 rot;

};
#endif