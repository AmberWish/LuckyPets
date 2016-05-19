#pragma once

#include <Windows.h>
#include <stdio.h>
#include "KMList.h"
#include <gl/gl.h>
#include <vector>
#include <iostream>

class KMWindow
{
public:
	KMWindow();
	int init();
	bool createWindow(WNDPROC WinProc, int mCmdShow);
	void render();
	void resize(GLsizei width, GLsizei height);
	HMENU createMenu();
	HWND createToolBar();
	void colorSelect();
	LRESULT dispatchEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	~KMWindow();
private:
	void renderLab1();
public:
	KMList vertex;
	HDC  hDC = NULL;
	HGLRC  hRC = NULL;
	HINSTANCE hInstance = NULL;
	HWND hMainWnd = NULL;
	GLuint PixelFormat;
	char* className = "Laba 1";
	HMENU hMenu;
	std::vector<KMList> vec;
	int lab = 0;
	int width = 0;
	int height = 0;
};