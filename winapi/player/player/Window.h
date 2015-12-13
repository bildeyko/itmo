#pragma once

#include <Windows.h>
#include "Action.h"

class Window 
{
	int height;
	int width;
	WNDCLASSEX wcex;
	HWND hWnd;
	int RegisterWindowClass();
public:
	Window(WNDPROC WndProc, HINSTANCE hInstance, TCHAR * szWindowClass);
	int createWindow(TCHAR* title, DataLoader* resources);
	void paint(int nCmdShow);
	MSG initMessageLoop();
	Action* action;	
};