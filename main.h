#pragma once

#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <GL\gl.h>
#include <GL\glu.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include "vector.h"
#include "Box.h"
#include "PairsGame.h"
#include "Mouse.h"
void rotateTiles(void);
void bounce(void);
void changeSize(int, int);
void computePos(float);
void computeDir(float);
void renderScene(void);
void pressKey(int, int, int);
void releaseKey(int, int, int);
float randColour(void);
void mouse(int, int, int, int);
void blackGround();
void initGL(void);
void drawRay(void);
void renderBegin(void);
void drawBoxes(void);
void initGlut(int, char**);
void registerCallbacks(void);
void calculateRay(int, int);
void debugUnprojectedCoords(void);
