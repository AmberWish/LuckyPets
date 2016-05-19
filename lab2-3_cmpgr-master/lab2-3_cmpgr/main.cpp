#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib,"glaux.lib")
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

#include <stdlib.h> 
#include <time.h>

int alpha = 0, beta = 0;
double x[50], y[50];

void initialize(double& x, double& y) //дает новые случайные координаты снежинкам
{
	x = -5 + (double)(rand() % 11000) / 1000;
	y = -5 + (double)(rand() % 11000) / 1000;
}

void getnewXY()	// перемещает снежинки по диагонали
{
	for (int i = 0; i < 50; i++)
	{
		if (x[i] < -5 || y[i] < -5)
		{
			initialize(x[i], y[i]);
		}
		else {
			x[i] -= 0.01;
			y[i] -= 0.01;
		}
	}
}

void CALLBACK mouse(AUX_EVENTREC *event)	//управление вращением сцены с помощью мыши
{
	static int x0, y0 = -12345;

	if (y0 != -12345)
	{
		alpha += event->data[AUX_MOUSEX] - x0;
		beta += event->data[AUX_MOUSEY] - y0;
	}

	x0 = event->data[AUX_MOUSEX];
	y0 = event->data[AUX_MOUSEY];
}

void CALLBACK Key_LEFT(void)	//вращение сценой при помощи стрелки влево
{
	alpha -= 5;
}

void CALLBACK Key_RIGHT(void) //вращение сценой при помощи стрелки вправо
{
	alpha += 5;
}


void CALLBACK Key_UP(void) //вращение сценой при помощи стрелки вверх
{
	beta += 5;
}

void CALLBACK Key_DOWN(void) //вращение сценой при помощи стрелки вниз
{
	beta -= 5;
}

void snowman() //отрисовка снеговика
{
	glPushMatrix();
	double c = 0.9;
	glColor4d(0.75, 0.75, 0.75, c);

	glTranslated(0, -3, 0);
	auxSolidSphere(2.0);

	glTranslated(0, 3, 0);
	auxSolidSphere(1.5);

	glColor4d(0.75, 0.75, 0.75, c);
	glTranslated(0, 2, 0);
	auxSolidSphere(1);

	glColor4d(0, 0, 0, c);
	glTranslated(-0.3, 0.3, 1);
	auxSolidSphere(0.1);
	
	glTranslated(0.6, 0, 0);
	auxSolidSphere(0.1);
	
	glTranslated(-0.3, -0.3, 0);
	glColor4d(1, 0, 0, c);
	auxSolidCone(0.3, 0.5);
	
	glTranslated(0, 0.75, -1);
	glColor4d(0, 0, 1, c);
	auxSolidCylinder(0.75, 2.);

	glPopMatrix();
}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glRotated(alpha, 0, 1, 0);
	glRotated(beta, -1, 0, 0);

	getnewXY();
	snowman();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	auxSwapBuffers();

}

void CALLBACK resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void main()
{
	float pos[4] = { 3, 3, 3, 1 };
	float dir[3] = { -1, -1, -1 };
	GLfloat mat_specular[] = { 1, 1, 1, 1 };

	srand(time(0));

	for (int i = 0; i < 50; i++)
	{
		initialize(x[i], y[i]);
	}

	auxInitPosition(50, 10, 400, 400);
	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);
	auxInitWindow("Controls");
	auxIdleFunc(display);
	auxReshapeFunc(resize);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	auxKeyFunc(AUX_LEFT, Key_LEFT);
	auxKeyFunc(AUX_RIGHT, Key_RIGHT);
	auxKeyFunc(AUX_UP, Key_UP);
	auxKeyFunc(AUX_DOWN, Key_DOWN);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSELOC, mouse);

	auxMainLoop(display);
}