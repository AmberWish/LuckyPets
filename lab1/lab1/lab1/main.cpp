#include "KMWindow.h"
//#include <Windows.h>
#include <tchar.h>

//#include <gl/gl.h>
#include <gl/glu.h>

GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
int InitGL(GLvoid);
//DrawGLScene
//KillGLWindow
HMENU createMenu();
HDC  hDC = NULL;
HGLRC  hRC = NULL;
HINSTANCE hInstance = NULL;
HWND hMainWnd = NULL;
KMWindow wnd;
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)        // Изменить размер и инициализировать окно GL
{
	if (height == 0)              // Предотвращение деления на ноль
		height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);            // Выбор матрицы проекций
	glLoadIdentity();              // Сброс матрицы проекции

								   // Вычисление соотношения геометрических размеров для окна
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);            // Выбор матрицы вида модели
	glLoadIdentity();              // Сброс матрицы вида модели
}

int InitGL(GLvoid)
{

	glShadeModel(GL_FLAT);
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return true;
}

int DrawGLScene(GLvoid)
{
	//glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана
															// и буфера глубины
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 1.0f, 0.0f);  // Вверх
	glColor3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);  // Слева снизу
	glVertex3f(1.0f, -1.0f, 0.0f);  // Справа снизу
	glVertex3f(1.5f, 0.5f, 0.0f);
	glEnd();

	glTranslatef(1.0f, 0.0f, 0.0f);
	glRotated(170.5f, -1.0f, 2.0f, 0.0f);

	glColor3f(0.1f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 1.0f, 0.0f);  // Слева вверху
	glVertex3f(1.0f, 1.0f, 0.0f);  // Справа вверху
	glVertex3f(1.0f, -1.0f, 0.0f);  // Справа внизу
	glVertex3f(-1.0f, -1.0f, 0.0f);  // Слева внизу
	glEnd();

	return 0;
}

GLvoid KillGLWindow(GLvoid)
{
	ChangeDisplaySettings(NULL, 0);
	ShowCursor(true);

	if (hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hMainWnd, hDC))
		hDC = NULL;

	if (hMainWnd && !DestroyWindow(hMainWnd))
		hMainWnd = NULL;

	if (!UnregisterClass((LPCWSTR)"OpenGL", hInstance))
		hInstance = NULL;

}

int WINAPI WinMain(HINSTANCE hInstanceBase, HINSTANCE hPrevInstance, LPSTR lpCmpLine, int mCmdShow)
{
	MSG msg;
	wnd.createWindow(WinProc, mCmdShow);

	wnd.init();

	/*
	GLuint PixelFormat;
	char className[] = "OpenGL";
	MSG msg;
	WNDCLASSEX wc;
	hInstance = hInstanceBase;

	RECT WRect;

	WRect.left = (long)0;
	WRect.bottom = 300;
	WRect.right = 300;
	WRect.top = (long)0;

	DEVMODE dm;

	memset(&dm, 0, sizeof(dm));

	dm.dmSize = sizeof(dm);
	dm.dmPelsWidth = 300;
	dm.dmPelsHeight = 300;
	dm.dmBitsPerPel = 32;
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	AdjustWindowRectEx(&WRect, dwStyle, false, dwExStyle);

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCWSTR)className;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
		return 0;

	hMainWnd = CreateWindowEx(0, (LPCWSTR)className, _T("Application"), WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL | WS_MINIMIZEBOX,
		                      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, (HWND)NULL, (HMENU)NULL,(HINSTANCE)hInstance, NULL);

	if (!hMainWnd)
		return 0;


	static  PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_COMPOSITION | PFD_DOUBLEBUFFER,//PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0, 
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	/////////////////////////////////
	if (!(hDC = GetDC(hMainWnd)))
	{
		KillGLWindow();
		return false;
	}
	
		if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
		{
			KillGLWindow();
			return false;
		}

		if (!SetPixelFormat(hDC, PixelFormat, &pfd))
		{
			KillGLWindow();
			return false;
		}

		if (!(hRC = wglCreateContext(hDC)))
		{
			KillGLWindow();
			return false;
		}

		if (!wglMakeCurrent(hDC, hRC))
		{
			KillGLWindow();
			return false; 
		}
		
	SetMenu(hMainWnd, createMenu());
	DrawMenuBar(hMainWnd);

		if (!InitGL())
		{
			KillGLWindow();
			return false;
		}

	/////////////////////////////
*/

    SetMenu(wnd.hMainWnd, wnd.createMenu());
	ShowWindow(wnd.hMainWnd, mCmdShow);
	UpdateWindow(wnd.hMainWnd);
	//wnd.createToolBar();
	//wnd.colorSelect();


	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return wnd.dispatchEvent(hWnd, uMsg, wParam, lParam);
/*
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_MOUSEMOVE:

		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_SIZE:
		//ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
		wnd.resize(LOWORD(lParam), HIWORD(lParam));
		wnd.render();
		//DrawGLScene();
		SwapBuffers(wnd.hDC);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
*/
}

HMENU createMenu()
{
	HMENU menu = CreateMenu();

	HMENU popMenu = CreatePopupMenu();

	InsertMenu(menu, 0, MF_BYCOMMAND | MF_STRING | MF_POPUP, (UINT)popMenu, L"&Laba");
	InsertMenu(menu, 0, MF_BYCOMMAND | MF_STRING | MF_POPUP, 0, L"&File");

	MENUITEMINFOW itemInfo;
	int size = sizeof(MENUITEMINFOW);
	itemInfo.cbSize =  sizeof(MENUITEMINFOW);
	itemInfo.fMask = MIIM_STATE | MIIM_FTYPE | MIIM_STRING;
	itemInfo.fType = MFT_STRING;
	itemInfo.fState = MFS_ENABLED;
	itemInfo.dwTypeData = L"File";
	itemInfo.cch = 4;

	size = sizeof(MENUITEMINFOW);

	bool u = InsertMenuItem(popMenu, 0, false, &itemInfo);
	//bool h = AppendMenu(popMenu, MF_BYCOMMAND, 5, L"111");
	// h = AppendMenu(popMenu, MF_BYCOMMAND, 4, L"22");

	DWORD gg = GetLastError();

	return menu;
}