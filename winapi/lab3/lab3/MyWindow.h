#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <Windows.h>

class MyWindow {
	HWND hWnd;
	WNDCLASSEX wcex;
	HINSTANCE hInst;	
	static BOOL isReg;

	void RegClass(LPTSTR className);	
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static int count;
public:
	MyWindow(HINSTANCE hInstance, LPTSTR windowName, int width, int height);
	HWND GetWnd();
	void ShowWindow(int nCmdShow = SW_SHOWNORMAL);
	void UpdateWindow();
	void DestroyWindow();
};

#endif
