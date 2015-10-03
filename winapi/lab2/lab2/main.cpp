#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shobjidl.h> 

#define MAX_LOADSTRING 100
#define SINBUTTON_ID 1
#define COSBUTTON_ID 2
#define X1TEXT_ID 3 
#define X2TEXT_ID 4 
#define LINEWIDTH_ID 5
#define CHARBUFLENGTH 6

HINSTANCE hInst;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	static TCHAR szAppName[] = L"MainWindow";
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	RegisterClassEx(&wcex);

	hInst = hInstance;
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		szAppName,
		L"Lab 1",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		710, 710,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc, hmdc;
	BITMAP bm, mbm;
	COLORREF color, newColor;

	TCHAR x1Lbl[] = L"X1";
	TCHAR x2Lbl[] = L"X2";
	TCHAR widthLbl[] = L"Line width";
	TCHAR colorsLbl[] = L"Colors";

	switch (message) {
	case WM_CREATE:
		HWND hStart, hEnd, hWidth, hColorSin, hColorCos;
		hStart = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT, 85, 10, 50, 20, hWnd, (HMENU)X1TEXT_ID, hInst, 0);
		hEnd = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT, 85, 40, 50, 20, hWnd, (HMENU)X2TEXT_ID, hInst, 0);
		hWidth = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 85, 70, 50, 20, hWnd, (HMENU)LINEWIDTH_ID, hInst, 0);
		hColorSin = CreateWindow(L"Button", NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 132, 50, 20, hWnd, (HMENU)SINBUTTON_ID, hInst, 0);
		hColorCos = CreateWindow(L"Button", NULL, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 85, 132, 50, 20, hWnd, (HMENU)COSBUTTON_ID, hInst, 0);
		
		SetWindowText(hStart, L"-10");
		SetWindowText(hEnd, L"10");
		SetWindowText(hWidth, L"1");
		SetWindowText(hColorSin, L"sin(x)");
		SetWindowText(hColorCos, L"cos(x)");
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 12, x1Lbl, _tcslen(x1Lbl));
		TextOut(hdc, 10, 42, x2Lbl, _tcslen(x2Lbl));
		TextOut(hdc, 10, 72, widthLbl, _tcslen(widthLbl));
		TextOut(hdc, 52, 102, colorsLbl, _tcslen(colorsLbl));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
