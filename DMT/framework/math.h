
#ifndef _SIMATH_
#define _SIMATH_
#include "..\glm\glm\glm.hpp"
#include "..\glm\glm\gtc\matrix_transform.hpp"
#include "..\glm\glm\gtc\type_ptr.hpp"
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::perspective;
using glm::translate;
using glm::scale;
using glm::max;
using glm::min;
/*
struct vert3 {
public:
	vert3():x(0),y(0),z(0) {}
	vert3(float X,float Y,float Z):x(X),y(Y),z(Z) {}
	union {
		struct {
			float x;
			float y;
			float z;
		};
		float data[3];
	};
};

struct vert4 {
public:
	vert4():x(0),y(0),z(0),w(0) {}
	vert4(float X,float Y,float Z,float W):x(X),y(Y),z(Z),w(W) {}
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float data[4];
	};
}; 

struct mat4 {

};
*/
#endif