#include <Windows.h>
#include <tchar.h>
#include "Application.h"
#include "MyWindow.h"

Application::Application(HINSTANCE hInstance) {
	hInst = hInstance;

	MyWindow window1(hInst, "Window 1", 500, 500);
	window1.ShowWindow();
	window1.UpdateWindow();

	MyWindow window2(hInst, "Window 2", 300, 100);
	window2.ShowWindow();
	window2.UpdateWindow();
}

int Application::Run() {
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}