#include <Windows.h>

#include <gl/gl.h>
#include "gl/glut.h"
#include <gl/glu.h>
#include <cmath>
#include <algorithm>
#include <gl/GLAux.h>

#pragma comment(lib, "Glaux.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "OpenGL32.lib")
void init();
void display();
void mouse(int, int, int, int);
void callInLoop();
void mousePressed(int x, int y);
void displayText(float x, float y, float z, float r, float g, float b, const char *string);
void doScale();
void rotate();
void setColor(GLfloat[]);
void setColor(GLfloat r, GLfloat g, GLfloat b);
void keyboardHandler(unsigned char key, int x, int y);
void loadTexture();
void paintBee();
struct GLCoord{
	double x, y;
};
GLCoord ConvertMouseCoord(POINT);
GLCoord ScreenToGL(int x, int y);
void displayAxis();
void cube(double x, double y, double z, double a);