#include "Mouse.h"
#include "main.h"
using namespace std;



Mouse::Mouse() : position(0, 0, 0), BVposition(0, 0, 0) {
	intersect = false;
	BoundSphereRadius = 1.0;
	BVposition.x = position.x + 0.5;
	BVposition.y = position.y - 0.25;
	BVposition.z = position.z - 0.5;
}
void Mouse::mouse(int button, int state, int x, int y)
{
	Mouse raymouse;
	int view[4];
	//   double modelview[16];
	double proj[16];
	glGetIntegerv(GL_VIEWPORT, view);
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	int realy = view[3] - (GLint)y - 1;
	int check = gluUnProject(x, realy, -1, WorldT, proj, view, objectNear, objectNear + 1, objectNear + 2);
	cout << "unprojected near co-ords are ";
	for (int i = 0; i<4; i++) {
		cout << objectNear[i] << " ";
	} cout << "\n";
	check = gluUnProject(x, realy, 1, WorldT, proj, view, objectFar, objectFar + 1, objectFar + 2);
	cout << "unprojected far co-ords are ";
	for (int i = 0; i<4; i++) {
		cout << objectFar[i] << " ";
	} cout << "\n";
	//prepare for collision test by making a ray
	Vector d(objectFar[0], objectFar[1], objectFar[2]);
	Vector p(objectNear[0], objectNear[1], objectNear[2]);
	Ray ray1;  //this is the ray cast
	ray1.SetOrigin(p);      //initialise ray with origin and direction vector
	ray1.SetDirection(d - p);
	if (raymouse.isBoundSphereIntersect(ray1))
		cout << "hit" << endl;
	else
		cout << "miss" << endl;

	glTranslatef(BVposition.x, BVposition.y, BVposition.z);
	glutPostRedisplay();



}

bool Mouse::isBoundSphereIntersect(Ray v) {
	//calc collision
	cout << "line point distance squared is: " << v.LinePointDistanceSqd(BVposition) << "\n";


	if (v.LinePointDistanceSqd(BVposition)>(BoundSphereRadius*BoundSphereRadius))
		return false; //no intersection detected
	else true;//intersection detected
	
}



Mouse::~Mouse()
{
}
