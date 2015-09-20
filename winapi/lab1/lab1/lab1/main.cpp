#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shobjidl.h> 

HINSTANCE hInst; // спросить про стиль
HANDLE  hBitmap, hMaskBitmap;


ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	hBitmap = LoadImage(hInst, L"C:\\Users\\ASUS\\Desktop\\WinAPI\\WinAPI\\Задание 1\\test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	hMaskBitmap = LoadImage(hInst, L"C:\\Users\\ASUS\\Desktop\\WinAPI\\WinAPI\\Задание 1\\1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	if (hBitmap == NULL || hMaskBitmap == NULL) {
		MessageBox(NULL, L"Can't open image", L"Error", MB_ICONEXCLAMATION);
		return 0;
	}
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance) {
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
	wcex.lpszClassName = L"APP_NAME";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	HWND hWnd;

	hInst = hInstance; 
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, 
		L"Lab 1", 
		L"Lab 1", 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		710, 710, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);
	if (!hWnd) {
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc, hmdc;
	BITMAP bm, mbm;
	COLORREF color, newColor;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (true) {
			hmdc = CreateCompatibleDC(hdc);
			GetObject(hBitmap, sizeof(bm), (LPSTR)&bm);
			GetObject(hMaskBitmap, sizeof(mbm), (LPSTR)&mbm);
			SelectObject(hmdc, hBitmap);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hmdc, 0, 0, SRCCOPY);
			SelectObject(hmdc, hMaskBitmap);
			for (int i = 0; i < mbm.bmHeight; i++) {
				for (int j = 0; j < mbm.bmWidth; j++) {
					color = GetPixel(hmdc, j, i);
					if ((GetRValue(color) == 0) && (GetGValue(color) == 0) && (GetBValue(color) == 0)) {
						newColor = GetPixel(hdc, (bm.bmWidth - mbm.bmWidth) + j, bm.bmHeight - mbm.bmHeight + i);
						SetPixel(hdc, (bm.bmWidth - mbm.bmWidth) + j, bm.bmHeight - mbm.bmHeight + i,
							RGB(GetRValue(newColor), GetGValue(newColor) * 0.5>255 ? 255 : GetGValue(newColor) *0.5, GetBValue(newColor)));
					}
				}
			}

			DeleteObject(hBitmap);
			DeleteObject(hMaskBitmap);
			DeleteDC(hmdc);
		}

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
