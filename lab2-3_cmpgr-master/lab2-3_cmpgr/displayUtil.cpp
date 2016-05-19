/*
#include "header.h"

double spinHor = 0;
double spinVer = 0;
double scale = 1.5;
void setColor(GLfloat color[]){
	glColor3fv(color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);
}
void setColor(GLfloat r, GLfloat g, GLfloat b){
	GLfloat color[] = { r, g, b, 1 };
	setColor(color);
}
void doScale(){
	glScaled(scale, scale, scale);
}
void displayAxis(){
	setColor(1, 0, 0);
	glBegin(GL_LINES);
	
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0.95, 0, 0.05);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0.95, 0, -0.05);
	glEnd();
	displayText(0.9, 0, 0, 1, 0, 0, "X");
	setColor(0, 1, 0);
	glBegin(GL_LINES);
	
	glVertex3f(0, -1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0.05, 0.95, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(-0.05, 0.95, 0);
	glEnd();
	displayText(0, 0.9, 0, 0, 1, 0, "Y");
	setColor(0, 0, 1);
	glBegin(GL_LINES);
	
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 1);
	glVertex3f(0.05, 0, 0.95);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(-0.05, 0, 0.95);
	glEnd();
	displayText(0, 0, 0.9, 0, 0, 1, "Z");
}




static double curx = 0, cury = 0;

void mousePressed(int x, int y){

	GLCoord point = ScreenToGL(x, y);

	spinHor += -100 * (curx - point.x);
	spinVer += 100 * (cury - point.y);


	curx = point.x;
	cury = point.y;

}

void mouse(int button, int state, int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:

		if (state == GLUT_DOWN){


			GLCoord point = ScreenToGL(x, y);

			curx = point.x;
			cury = point.y;



		}
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}


void rotate(){
	glRotatef(30 + spinVer, 1, 0, 0);
	glRotatef(spinHor - 30, 0, 1, 0);


	//spinHor = 0;
}
extern bool doFly;
void keyboardHandler(unsigned char key, int x, int y){
	switch (key)
	{
	case '+':
		scale *= 1.2;
		break;
	case '-':
		scale *= 0.8;
		break;
	case ' ':
		doFly = !doFly;
	default:
		break;
	}

}
unsigned int textures[1];
void loadTexture(){
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("texture.bmp");
	// Создание текстуры
	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 2, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}
extern double dFly;

void paintBee(){
	
	
	//середина тела
	glPushMatrix();

	glColor3f(1, 1, 1);
	glScaled(1, 0.5, 0.5);
	//glTranslated(0.5, 0.5, 0);
	/////////////сфера с текстурой
	GLUquadricObj *q; // Квадратичный объект для рисования сферы
	q = gluNewQuadric(); // Создать квадратичный объект
	// тип генерируемых нормалей для него – «сглаженные»
	gluQuadricNormals(q, GL_SMOOTH);
	// Включить текстурные координаты для объекта
	gluQuadricTexture(q, GL_TRUE);
	// Настройка сферического наложения
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	// Настройка отображения сферы
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//glPushMatrix();
	glEnable(GL_TEXTURE_2D); // Разрешение наложение текстуры
	glRotatef(90, 0, 1, 0);
	setColor(1, 1, 0);
	gluSphere(q, 0.5, 20, 20);
	//glutSolidSphere(0.5, 40, 40);
	
	
	glPopMatrix();
	//конец середины тела
	//задняя часть тела
	glPushMatrix();
	glTranslatef(-0.2, 0, 0);
	glPushMatrix();
	setColor(1, 1, 1);
	glColor3f(1, 1, 1);

	glRotatef(35, 0, 0, 1);
	glTranslated(-0.5, 0, 0);

	glPushMatrix();
	glScaled(0.8, 0.4, 0.4);
	glRotatef(90, 0, 1, 0);
	setColor(1, 1, 0);
	gluSphere(q, 0.5, 40, 40);
	//glutSolidSphere(0.5, 40, 40);
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D); // Разрешение наложение текстуры
	//конец задней части тела
	//жало
	glPushMatrix();
	setColor(0.2, 0.2, 0.2);
	glScalef(0.55, 0.55, 0.55);
	glRotatef(180, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(-60, 1, 0, 0);
	glTranslated(0, 0, 0.5);
	glTranslated(0, -0.5, 0.8);
	glScalef(0.5, 0.5, 0.5);

	glutSolidCone(0.5, 1, 20, 20);
	//glutSolidSphere(0.5, 40, 40);
	glPopMatrix();

	//конец жала
	
	glPopMatrix();
	//glutWireCube(1.0);
	//крыло левое
	setColor(1, 1, 1);
	glPushMatrix();
	glRotatef(15 + dFly, 1, 0, 0);
	glTranslatef(0, 0, -0.5);
	glPushMatrix();
	glScalef(0.4, 0.01, 0.8);
	glutSolidSphere(0.8, 20, 20);
	glPopMatrix();
	glPopMatrix();
	//конец левого крыла
	//крыло правое
	glPushMatrix();
	setColor(1, 1, 1);
	glRotatef(165 - dFly, 1, 0, 0);
	glTranslatef(0, 0, -0.5);
	glPushMatrix();
	glScalef(0.4, 0.01, 0.8);
	glutSolidSphere(0.8, 20, 20);
	glPopMatrix();
	glPopMatrix();
	//конец правого крыла
	//голова
	setColor(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(0.5, -0.1, 0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();
	//конец головы
	
}
*/