#include "main.h"
using namespace std;

bool tilesGenerated = false;

PairsGame game;
static int theta = 4;
//float xpos= 5.0*sin(float(theta)*0.0175), ypos=10.0, zpos= 5.0*cos(float(theta)*0.0175);
int winview[2]; //contains window view width [0] and height [1]
double WorldT[16];
double objectNear[4];
double objectFar[4];
// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 3.0f, z = 1.0f;
//gl camerapos;

bool movingUp = false; // Whether or not we are moving up or down
float yLocation = 0.0f; // Keep track of our position on the y axis.

float yRotationAngle = 0.0f; // The angle of rotation for our object
// the key states. These variables will be zero
//when no key is being presses
float deltaMove = 0;
float deltaAngle = 0.0f;

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		calculateRay(x, y);

        //prepare for collision test by making a ray
		Vector d(objectFar[0], objectFar[1], objectFar[2]);
		Vector p(objectNear[0], objectNear[1], objectNear[2]);

		Ray ray1;
		ray1.SetOrigin(p);
		ray1.SetDirection(d - p);

        for (Box box : game.boxes) {
            if(box.isBoundSphereIntersect(ray1)) {
                cout << "hit box " << box.x << ", " << box.z << endl;
            }
        }

		glutPostRedisplay();

	}

}

void calculateRay(int x, int y) {
    int view[4];
    double proj[16];
    glGetIntegerv(GL_VIEWPORT, view);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    int realy = view[3] - (GLint)y - 1;

    gluUnProject(x, realy, -1, WorldT, proj, view, objectNear, objectNear + 1, objectNear + 2);
    gluUnProject(x, realy, 1, WorldT, proj, view, objectFar, objectFar + 1, objectFar + 2);

    //debugUnprojectedCoords();
}

void debugUnprojectedCoords() {
    cout << "unprojected near co-ords are ";
    for (int i = 0; i<4; i++) {
        cout << objectNear[i] << " ";
    } cout << "\n";

    cout << "unprojected far co-ords are ";
    for (int i = 0; i<4; i++)
    {
        cout << objectFar[i] << " ";
    } cout << "\n";
}


void bounce()
{
	if (movingUp) // If we are moving up
		yLocation -= 0.005f; // Move up along our yLocation
	else  // Otherwise
		yLocation += 0.005f; // Move down along our yLocation

	if (yLocation < -3.0f) // If we have gone up too far
		movingUp = false; // Reverse our direction so we are moving down
	else if (yLocation > 3.0f) // Else if we have gone down too far
		movingUp = true; // Reverse our direction so we are moving up
	glTranslatef(0.0f, yLocation, 0.0f); // Translate our object along the y axis


}


void changeSize(int w, int h) {
	//GLfloat nRange = 100.0f;
	glViewport(0, 0, w, h);
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;
	// Set the viewport to be the entire window

	// Reset Matrix
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//             l,r,bot,top,near,far
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Set the correct perspective.
	gluPerspective(60.0f, ratio, 1.0f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
	winview[0] = w; winview[1] = h;
	glLoadIdentity();
}


void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}

void renderScene(void) {
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

    renderBegin();

	drawRay();

	drawBoxes();

	glutSwapBuffers();
}

void drawBoxes() {
    for (Box box : game.boxes) {
		glPushMatrix();
		glTranslatef(box.x, box.y, box.z);

		glColor3f(box.r, box.g, box.b);
		box.draw();
		glPopMatrix();
	}
}

void renderBegin() {
    // Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	// Reset transformations
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(4.0, 2.0, 0.001, 100000);
	gluPerspective(45.0f, (GLfloat)800 / (GLfloat)600, 5.0f, 10000.0f); // We define the "viewing volume"
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	gluLookAt(5.0*sin(float(theta)*0.0175), 10.0, 5.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glGetDoublev(GL_MODELVIEW_MATRIX, WorldT);//get for use with gluUnproject
}

void drawRay() {
    glBegin(GL_TRIANGLES);  //fire ray
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3d(objectNear[0], objectNear[1], objectNear[2]);
	glVertex3d(objectFar[0], objectFar[1], objectFar[2]);
	glVertex3d(objectNear[0] + 0.1, objectNear[1], objectNear[2]);
	glEnd();
}

void blackGround()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT:
		deltaAngle = -0.01f;
		break;
	case GLUT_KEY_RIGHT:
		deltaAngle = 0.01f;
		break;
	case GLUT_KEY_UP:
		deltaMove = 0.5f;
		break;
	case GLUT_KEY_DOWN:
		deltaMove = -0.5f;
		break;
	case GLUT_KEY_END:
		yLocation = 0.5;
		game.ShuffleBoxes();
		break;
	case GLUT_KEY_INSERT:
		yRotationAngle = -45.0f;
		break;
	}
}

void releaseKey(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:
		deltaAngle = 0.0f;
		break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:
		deltaMove = 0;
		break;
	case GLUT_KEY_END:
		yRotationAngle = 0;
		break;
	}
}

float randColour()
{
	return (double)rand() / (RAND_MAX + 1.0);
}

int main(int argc, char **argv) {
    initGlut(argc, argv);

    registerCallbacks();

	// here are the new entries
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	initGL();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}

void registerCallbacks() {
    // register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(pressKey);
	glutMouseFunc(mouse);
}

void initGL(void)
{
    glEnable(GL_DEPTH_TEST);
	glPushMatrix();

	WorldT[0] = 1; WorldT[4] = 0; WorldT[8] = 0; WorldT[12] = 0;
	WorldT[1] = 0; WorldT[5] = 1; WorldT[9] = 0; WorldT[13] = 0;
	WorldT[2] = 0; WorldT[6] = 0; WorldT[10] = 1; WorldT[14] = 0;
	WorldT[3] = 0; WorldT[7] = 0; WorldT[11] = 0; WorldT[15] = 1;

	blackGround();  //reset "empty" background colour
	glShadeModel(GL_SMOOTH);

	glutInitDisplayMode(GLUT_DEPTH);
}

void initGlut(int argc, char **argv) {
    // init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Match Game: Tile Madness!");
}

void rotateTiles()
{
	yRotationAngle += 0.005f; // Increment our rotation value
	if (yRotationAngle > 360.0f) // If we have rotated beyond 360 degrees (a full rotation)
		yRotationAngle -= 360.0f; // Subtract 360 degrees off of our rotation
	glRotatef(yRotationAngle, 0.0f, 0.0f, 1.0f); // Rotate our object around the y axis

}
