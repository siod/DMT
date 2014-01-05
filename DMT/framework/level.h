#ifndef _LEVEL_
#define _LEVEL_
#include "..\renderer\model.h"
#include "math.h"
#include <vector>
typedef std::vector<guid> entityList;
class Level {

public:
	enum STATE {
		STATE_ERROR,
		STATE_OK,
	};


	Level():id(0),state(STATE_ERROR),startPos(0.0f,0.0f,0.0f),
		name("INVALID"),friendlyName("unloaded level"),entites() {}


	guid id;
	STATE state;
	vec3 startPos;
	SiString name;
	SiString friendlyName;
	entityList entites;

};
#endif
