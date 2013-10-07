
#ifndef _SIMATH_
#define _SIMATH_
class vert3 {
public:
	vert3():x(0),y(0),z(0) {}
	vert3(float X,float Y,float Z):x(X),y(Y),z(Z) {}
	float x;
	float y;
	float z;
};

class vert4 {
public:
	vert4():x(0),y(0),z(0),w(0) {}
	vert4(float X,float Y,float Z,float W):x(X),y(Y),z(Z),w(W) {}
	float x;
	float y;
	float z;
	float w;
}; 
#endif