#pragma once
#include "Vector.h"
class Mouse
{
public:
	double WorldT[16];
	double objectNear[4];
	double objectFar[4];

	Mouse();
	
	bool isBoundSphereIntersect(Ray v);
	void draw();
	void mouse(int button, int state, int x, int y);

	bool intersect;
	float BoundSphereRadius;
	Vector position; //point
	Vector BVposition;//point
	~Mouse();
};

