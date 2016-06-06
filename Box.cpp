#include "Box.h"
#include "main.h"
using namespace std;

Box::Box(GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat red, GLfloat green, GLfloat blue) : position(0, 0, 0), BVposition(0, 0, 0) {
	x = xPos;
	y = yPos;
	z = zPos;
	r = red;
	g = green;
	b = blue;

	intersect = false;
	BoundSphereRadius = 0.5f;
	BVposition.x = position.x+ x;
	BVposition.y = position.y- y;
	BVposition.z = position.z- z;
}


Box::~Box()
{
}

void Box::draw() {
    glutWireCube(1);
}

bool Box::isBoundSphereIntersect(Ray v) {
	//calc collision
	float dist = v.LinePointDistanceSqd(Vector(x,y,z));

	if (dist > (BoundSphereRadius)) {
		return false;
	} else {
        cout << "line point distance squared is: " << dist << "\n";
        return true;
    }
}
