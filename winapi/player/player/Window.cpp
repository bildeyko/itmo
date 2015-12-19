#include "Window.h"

Window::Window(WNDPROC WndProc, HINSTANCE hInstance, TCHAR * szWindowClass)
{
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL; //(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
}

int Window::createWindow(TCHAR* title, DataLoader* resources) {

	//set window size
	BITMAP bm;
	HBITMAP hMask = resources->getHBackgroundMask8bit();
	GetObject(hMask, sizeof(bm), &bm);
	this->height = bm.bmHeight;
	this->width = bm.bmWidth;

	//initialize visible form worker
	this->action = new Action(resources, this->height, this->width);

	if (RegisterWindowClass()) return 1;
	hWnd = CreateWindow(
		wcex.lpszClassName,
		title,
		WS_POPUP,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - height) / 2,		
		width, height,
		NULL,
		NULL,
		wcex.hInstance,
		NULL
		);
	if (!hWnd) {
		MessageBox(NULL,
			("Call to CreateWindow failed!"),
			("Error"),
			NULL);
		return 1;
	}
	HRGN hWindowRegion = action->BitMapToHRGN(resources->getHBackgroundMask8bit());
	SetWindowRgn(hWnd, hWindowRegion, TRUE);

	DeleteObject(hWindowRegion);
	return 0;
}

int Window::RegisterWindowClass() {
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL,
			("Call to RegisterClassEx failed!"),
			("Win32 Guided Tour"),
			NULL);
		return 1;
	}
	return 0;
}

void Window::paint(int nCmdShow) {
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

MSG Window::initMessageLoop() {
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg;
}