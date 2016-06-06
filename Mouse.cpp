#include "Mouse.h"
#include "main.h"
using namespace std;



Mouse::Mouse() : position(0, 0, 0), BVposition(0, 0, 0) {
	intersect = false;
	BoundSphereRadius = 1.0;
	BVposition.x = position.x+ 0;
	BVposition.y = position.y- 0;
	BVposition.z = position.z- 0;
}


bool Mouse::isBoundSphereIntersect(Ray v) {
	//calc collision
	cout << "line point distance squared is: " << v.LinePointDistanceSqd(BVposition) << "\n";


	if (v.LinePointDistanceSqd(BVposition) > (BoundSphereRadius*BoundSphereRadius))
		return false; //no intersection detected
	else return true;//intersection detected
	
}



