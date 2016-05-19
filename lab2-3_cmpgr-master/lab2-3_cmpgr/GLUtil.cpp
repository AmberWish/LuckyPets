/*#include "header.h"
static int windowW = 600;
static int windowH = 600;
extern double spinHor;
void reshape(int w, int h){
	windowH = h;
	windowW = w;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	static bool f = 1;
	if (f){
		f = 0;
		//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
		//glLoadIdentity();
		//glRotatef(30, 1, 0, 0);
		//glRotatef(30 + spinHor, 0, -1, 0);
	}
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

static float ambient[4] = { 0.5, 0.5, 0.5, 1 };
float pos[4] = { 3, 3, 3, 1 };
float color[4] = { 1, 1, 1, 1 };
float sp[4] = { 1, 1, 1, 1 };
float mat_specular[] = { 1, 1, 1, 1 };
void init(){
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glutIdleFunc(callInLoop);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//освещение
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shiness[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 0.0, 2.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiness);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	//загрузка текстуры
	loadTexture();
	//glEnable(GL_TEXTURE_2D);
	//конец загрузки текстуры
	glEnable(GL_DEPTH_TEST);//удаление невидимых поверхностей
	//конец освещения
	/////
	glEnable(GL_NORMALIZE);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lab 2-3 by Ilia Volk");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mousePressed);
	glutKeyboardFunc(keyboardHandler);
	//glutReshapeFunc();передать функцию которая будет вызываться при изменении размера екрана
	//glutKeyBoardFunc(); передать функцию обработки событий клавиатуры
	//void (*func)(char key, int x, int y)
	//glutMouseFunc(); передать функцию обработки мыши
	//void (*func)(int button, int state, int x, int y)
	//glutMotiorFunc(); отклик на перемещение мыши при нажатой кнопке??
	//void (*func)(int x, int y)
	glutMainLoop();
	return 0;
}

GLCoord ConvertMouseCoord(POINT currentMouse){
	GLCoord mouseOpenGLCoord;
	float x = currentMouse.x;
	float h = windowH;
	float ax = 2 * x / h - 1;
	float y = currentMouse.y;
	float w = windowW;
	float ay = 2 * (w - y) / w - 1;

	mouseOpenGLCoord.x = ax;
	mouseOpenGLCoord.y = ay;;
	return mouseOpenGLCoord;
}
extern GLfloat spinZ;
GLCoord ScreenToGL(int x, int y){
	POINT p;
	p.x = x;
	p.y = y;

	return ConvertMouseCoord(p);
}


void displayText(float x, float y, float z, float r, float g, float b, const char *string) {
	int j = strlen(string);

	glColor3f(r, g, b);
	glRasterPos3f(x, y, z);
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
*/