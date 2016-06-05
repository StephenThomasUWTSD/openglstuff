#pragma once
#include "Vector.h"
class Mouse
{
public:
	

	Mouse();

	void sceneBound();
	
	bool isBoundSphereIntersect(Ray v);
	//void drawBox(float w, float h, float l);
	void draw();
	//void mouse(int button, int state, int x, int y);
//private:
	bool intersect;
	float BoundSphereRadius;
	//float sceneBoundSphereRadius;
	
	Vector BVposition;//point
	
	Vector position; //point
	//Vector BVposition;//point

	//~Mouse();
};

