#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <tchar.h>
#include "MyWindow.h"

BOOL MyWindow::isReg = FALSE;

MyWindow::MyWindow(HINSTANCE hInstance, LPTSTR windowName, int width, int height) {
	hInst = hInstance;
	TCHAR className[14];
	strcpy(className, "MyWindowClass");

	if (!isReg) {
		RegClass(className);
		isReg = TRUE;
	}

	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		className,
		windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInst,
		NULL);		
}

void MyWindow::RegClass(LPTSTR className) {
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MyWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = className;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	RegisterClassEx(&wcex);
}

LRESULT CALLBACK  MyWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	RECT rect;
	switch (message) {
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		DrawText(hdc, "Hello, laboratory work 3!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		// What to do in case without PostQuitMessage(0) when we close all windows?
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

HWND MyWindow::GetWnd() {
	return hWnd;
}

void MyWindow::ShowWindow(int nCmdShow) {
	::ShowWindow(hWnd, nCmdShow);
}

void MyWindow::UpdateWindow() {
	::UpdateWindow(hWnd);
}

void MyWindow::DestroyWindow() {
	::DestroyWindow(hWnd);
}