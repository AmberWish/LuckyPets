#include "KMWindow.h"
#include "resource.h"
#include <tchar.h>
#include <commctrl.h>
#include <Winuser.h>

#include <gl/glu.h>

#define ID_SELECT_COLOR     1001
#define ID_LAB_1            10001
#define ID_LAB_2            10002
#define ID_LAB_3            10003

/*******************************/
KMWindow::KMWindow()
{

}
/*******************************/
int KMWindow::init()
{
	printf("111");
	glShadeModel(GL_FLAT);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	INITCOMMONCONTROLSEX InitCtrlEx;

	InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrlEx.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&InitCtrlEx);

	return 0;
}
/*******************************/
bool KMWindow::createWindow(WNDPROC WinProc, int mCmdShow)
{
	WNDCLASSEX wc;
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
		return false;

	hMainWnd = CreateWindowEx(0, (LPCWSTR)className, _T("Application"), WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, (HWND)NULL, (HMENU)NULL, (HINSTANCE)hInstance, NULL);

	if (!hMainWnd)
		return false;


	static  PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_COMPOSITION | PFD_DOUBLEBUFFER,
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
		return false;

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
		return false;

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
		return false;

	if (!(hRC = wglCreateContext(hDC)))
		return false;

	if (!wglMakeCurrent(hDC, hRC))
		return false;
	//SwapBuffers(hDC);

	//ShowWindow(hMainWnd, mCmdShow);
	//UpdateWindow(hMainWnd);

	return true;
}
/*******************************/
/////////////////////////////////////////////////////////////////////////
int alpha = 0, beta = 0;
double x[50], y[50];

void initialize(double& x, double& y) //дает новые случайные координаты снежинкам
{
	x = -5 + (double)(rand() % 11000) / 1000;
	y = -5 + (double)(rand() % 11000) / 1000;
}
/*
void snowman() //отрисовка снеговика
{
	glPushMatrix();
	double c = 0.9;
	glColor4d(0.75, 0.75, 0.75, c);

	glTranslated(0, -3, 0);
	auxSolidSphere(2.0);

	glTranslated(0, 3, 0);
	auxSolidSphere(1.5);

	glPushMatrix();
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3d(0.9, 0.9, 0.9);
	glVertex3d(-1.4, 0, 0);
	glVertex3d(-2.5, 2, 0);

	glVertex3d(-2.5, 2, 0);
	glVertex3d(-3.3, 2.2, 0);

	glVertex3d(-2.5, 2, 0);
	glVertex3d(-3, 2.5, 0);

	glVertex3d(-2.5, 2, 0);
	glVertex3d(-2, 2.5, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glBegin(GL_LINES);
	glColor3d(0.9, 0.9, 0.9);
	glVertex3d(-1.4, 0, 0);
	glVertex3d(-2.5, 2, 0);

	glVertex3d(-2.5, 2, 0);
	glVertex3d(-3.3, 2.2, 0);

	glVertex3d(-2.5, 2, 0);
	glVertex3d(-3, 2.5, 0);

	glVertex3d(-2.5, 2, 0);
	glVertex3d(-2, 2.5, 0);
	glEnd();
	glPopMatrix();

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
	glRotated(-90, 1, 0, 0);
	auxSolidCone(0.75, 0.75);

	glPopMatrix();
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

void drawSnow(double x, double y)	//отрисовка снежинок
{
	glPushMatrix();
	glTranslated(x, y, 0);
	glColor3d(0.9, 0.9, 0.9);
	auxSolidSphere(0.1);
	glPopMatrix();
}
*/
//////////////////////////////////////////////////////////////////////////
void KMWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана														// и буфера глубины
	glLoadIdentity();

	if (lab == ID_LAB_1)
	{
		renderLab1();
	}
	else if (lab == ID_LAB_2)
	{
		/*
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glRotated(0, 0, 1, 0);
		glRotated(0, -1, 0, 0);

		for (int i = 0; i < 50; i++)
		{
			drawSnow(x[i], y[i]);
		}
		getnewXY();
		snowman();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		auxSwapBuffers();
		*/
	}
	else if (lab == ID_LAB_3)
	{

	}
}
void KMWindow::renderLab1()
{
	std::vector<KMList>::iterator it = vec.begin();

	for (it; it != vec.end(); it++)
	{
		KMList vertexTmp = *it;

		unsigned int color = vertexTmp.getColor();

		float red = (float)(color & 0xFF) / (float)0xFF;
		float green = (float)((color >> 8) & 0xFF) / (float)0xFF;
		float blue = (float)((color >> 16) & 0xFF) / (float)0xFF;
		glColor3f(red, green, blue);
		glBegin(GL_POLYGON);

		KMList::KMIterator it1(vertexTmp);
		for (it1.begin(); it1.end(); ++it1)
			glVertex3f((*it1).getX(), (*it1).getY(), (*it1).getZ());

		if (vertexTmp.getCurrent().getW() >= 0)
			glVertex3f(vertexTmp.getCurrent().getX(), vertexTmp.getCurrent().getY(), vertexTmp.getCurrent().getZ());
		glEnd();
	}

	unsigned int color = vertex.getColor();

	float red = (float)(color & 0xFF) / (float)0xFF;
	float green = (float)((color >> 8) & 0xFF) / (float)0xFF;
	float blue = (float)((color >> 16) & 0xFF) / (float)0xFF;
	glColor3f(red, green, blue);
	glBegin(GL_POLYGON);

	KMList::KMIterator it1(vertex);
	for (it1.begin(); it1.end(); ++it1)
		glVertex3f((*it1).getX(), (*it1).getY(), (*it1).getZ());

	if (vertex.getCurrent().getW() >= 0)
		glVertex3f(vertex.getCurrent().getX(), vertex.getCurrent().getY(), vertex.getCurrent().getZ());

	glEnd();
}
/*******************************/
void KMWindow::resize(GLsizei width, GLsizei height)
{
	if (lab == ID_LAB_1)
	{
		if (height == 0)
			height = 1;

		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(0.0, width, height, 0.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	else if (lab == ID_LAB_2)
	{
		/*
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-5, 5, -5, 5, 2, 12);
		gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
		glMatrixMode(GL_MODELVIEW);
		*/
	}
	else if (lab == ID_LAB_3)
	{

	}
}
/*******************************/
HMENU KMWindow::createMenu()
{
	HMENU menu = CreateMenu();

	HMENU popMenu = CreatePopupMenu();

	InsertMenu(menu, 0, MF_BYCOMMAND | MF_STRING | MF_POPUP, (UINT)popMenu, L"&Laba 1");
	InsertMenu(menu, 1, MF_BYCOMMAND | MF_STRING, ID_LAB_2, L"&Laba 2");
	InsertMenu(menu, 2, MF_BYCOMMAND | MF_STRING, ID_LAB_3, L"&Laba 3");

	AppendMenu(popMenu, MF_STRING, ID_SELECT_COLOR, L"Select Color");

	return menu;
}
/*******************************/
HWND KMWindow::createToolBar()
{
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | TBSTYLE_TOOLTIPS, 0, 0, 0, 0, hMainWnd, (HMENU)0, hInstance, NULL);
	HIMAGELIST hImageList = ImageList_Create(16, 16, ILC_COLOR16 | ILC_MASK, 3, 0);
	
	SendMessage(hWndToolbar, TB_SETIMAGELIST, (WPARAM)0, (LPARAM)hImageList);
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	TBBUTTON tbb[3] =
	{
		{ 0,0,TBSTATE_ENABLED,TBSTYLE_BUTTON },
		{ 1,1,TBSTATE_ENABLED,TBSTYLE_BUTTON },
		{ 2,2,TBSTATE_ENABLED,TBSTYLE_BUTTON },
	};

	SendMessage(hWndToolbar, (UINT)TB_ADDBUTTONS, 3, (LPARAM)&tbb);

	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hWndToolbar, SW_SHOW);
	
	return hWndToolbar;
}

void KMWindow::colorSelect()
{
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 
	//static DWORD rgbCurrent;        // initial color selection

									// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hMainWnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	//cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE)
	{
		vertex.setColor(cc.rgbResult);
	}
}
/*******************************/
LRESULT KMWindow::dispatchEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KMVector3f ver;

	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		ver.setX(lParam & 0xffff);
		ver.setY((lParam & 0xffff0000) >> 16);
		vertex.setCurrent(ver);
		render();
		SwapBuffers(hDC);
		break;

	case WM_COMMAND:
		if (wParam == ID_SELECT_COLOR)
		{
			colorSelect();
			lab = ID_LAB_1;
		}
		else if (wParam == ID_LAB_2)
		{
			lab = ID_LAB_2;
		}
		else if (wParam == ID_LAB_3)
		{
			lab = ID_LAB_3;
		}
		resize(width, height);
		break;

	case WM_LBUTTONDOWN:
		ver.setX(lParam&0xffff);
		ver.setY((lParam&0xffff0000)>>16);
		vertex.add(ver);
		render();
		SwapBuffers(hDC);
		break;

	case WM_RBUTTONDOWN:
		vertex.finish();
		vec.push_back(vertex);
		vertex.clean();
		render();
		SwapBuffers(hDC);
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		render();
		SwapBuffers(hDC);
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
/*******************************/
KMWindow::~KMWindow()
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

	if (!UnregisterClass((LPCWSTR)className, hInstance))
		hInstance = NULL;
}
/*******************************/