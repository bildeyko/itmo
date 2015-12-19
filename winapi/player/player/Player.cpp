#include <stdlib.h>
#include <Windows.h>
#include "DataLoader.h"
#include "Window.h"

TCHAR wndClassName[] = ("win32");
TCHAR title[] = ("Player");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Window* window;
DataLoader* resources;

int mouseState;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	resources = new DataLoader(hInstance);
	window = new Window(WndProc, hInstance, wndClassName);
	window->createWindow(title, resources);
	window->paint(nCmdShow);
	return (int)window->initMessageLoop().wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	POINT cursPt;

	switch (message) {
	case WM_CREATE:

		break;
	case WM_PAINT:
		window->action->paintBackground(hWnd);
		break;
	case WM_LBUTTONDOWN:
		int button;
		button = window->action->which_button(LOWORD(lParam), HIWORD(lParam));
		mouseState = 1;
		return TRUE;
	case WM_MOUSEMOVE:
		if (mouseState)
		{
			GetCursorPos(&cursPt);
			PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(cursPt.x, cursPt.y));
			mouseState = 0;
		}
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}