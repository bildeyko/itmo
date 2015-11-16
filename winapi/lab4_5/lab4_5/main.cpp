#include <Windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <math.h>

HINSTANCE hInst;

#define ACTIONSTYLEBUTTON_ID 1
#define SREEDTEXT_ID 2
#define SPEEDSUBMITBUTTON_ID 3

const int BALL_MOVE_DELTA = 10;

typedef struct _ballInfo
{
	int width;
	int height;
	int x;
	int y;

	int dx;
	int dy;

}ballInfo_t;

ballInfo_t ballInfo;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void UpdateBall(RECT* prc);
void DrawBall(HDC hdc, RECT* prc);


/*
	http://stackoverflow.com/questions/15324807/drawing-semitransparent-child-window-with-image-on-parent-window
	http://delphiru.ru/graphics/163-bitmap-motion.html
	http://www.winprog.org/tutorial/animation.html
	http://www.catch22.net/tuts/flicker-free-drawing
*/
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szAppName[] = "MainWindow";
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wcex;

	ballInfo.width = 100;
	ballInfo.height = 50;

	ballInfo.x = 300;
	ballInfo.y = 0;

	ballInfo.dx = BALL_MOVE_DELTA;
	ballInfo.dy = BALL_MOVE_DELTA;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(DKGRAY_BRUSH);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	RegisterClassEx(&wcex);

	hInst = hInstance;
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,
		szAppName,
		"Lab 4",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500, 800,
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static short direction = 1;
	const int ID_TIMER = 1;
	static int speed = 10;

	int wmId, wmEvent;
	HDC hdc;
	BOOL fError;
	RECT rcClient;

	BOOL mode = FALSE;
	

	switch (message) {
	case WM_CREATE:
		HWND hActionTypeButton, hSpeedText, hSpeedSubmit;
		hActionTypeButton = CreateWindow("button", "Automatically", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 10, 132, 120, 20, hWnd, (HMENU)ACTIONSTYLEBUTTON_ID, hInst, 0);
		hSpeedText = CreateWindow("Edit", "10", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 85, 10, 50, 20, hWnd, (HMENU)SREEDTEXT_ID, hInst, 0);
		hSpeedSubmit = CreateWindow("Button", "Ïèó!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 10, 50, 20, hWnd, (HMENU)SPEEDSUBMITBUTTON_ID, hInst, 0);
		break;
	case WM_PAINT:
		
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rcClient);

		UpdateBall(&rcClient);
		DrawBall(hdc, &rcClient);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			if (mode == TRUE)
				ballInfo.dy = -ballInfo.dy;
			else {
				if (ballInfo.dy > 0)
					ballInfo.dy = -ballInfo.dy;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		case VK_DOWN:
			if (mode == TRUE)
				ballInfo.dy = -ballInfo.dy;
			else {
				if (ballInfo.dy < 0)
					ballInfo.dy = -ballInfo.dy;		
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		default:
			break;
		}
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case ACTIONSTYLEBUTTON_ID:
			if (SendMessage(GetDlgItem(hWnd, ACTIONSTYLEBUTTON_ID), BM_GETCHECK, 0, 0) == BST_CHECKED) {
				SetTimer(hWnd, ID_TIMER, speed, NULL);
				mode = TRUE;
			}
			else {
				KillTimer(hWnd, ID_TIMER);
				mode = FALSE;
			}
			SetFocus(hWnd);
			break;
		case SPEEDSUBMITBUTTON_ID:
			if(ballInfo.dy < 0)
				ballInfo.dy = -(int)GetDlgItemInt(hWnd, SREEDTEXT_ID, &fError, TRUE);
			else
				ballInfo.dy = GetDlgItemInt(hWnd, SREEDTEXT_ID, &fError, TRUE);
			SetFocus(hWnd);
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		hdc = GetDC(hWnd);

		GetClientRect(hWnd, &rcClient);

		UpdateBall(&rcClient);
		DrawBall(hdc, &rcClient);

		ReleaseDC(hWnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void UpdateBall(RECT* prc)
{
	ballInfo.y += ballInfo.dy;

	if (ballInfo.y < 0)
		ballInfo.y = 0;
	else if (ballInfo.y + ballInfo.height > prc->bottom)
		ballInfo.y = prc->bottom - ballInfo.height;
}

void DrawBall(HDC hdc, RECT* prc)
{
	/*
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
	SelectObject(hdcBuffer, hbmBuffer);
	//PatBlt(hdcBuffer, 0, 0, prc->right, prc->bottom, WHITENESS);
	BitBlt(hdcBuffer, 0, 0, prc->right, prc->bottom, hdc, 0, 0, SRCCOPY);
	Ellipse(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.x + ballInfo.width, ballInfo.y + ballInfo.height);
	
	BitBlt(hdc, 200, 0, prc->right-200, prc->bottom, hdcBuffer, 200, 0, SRCCOPY);
	//BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);

	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
	//PAINTSTRUCT ps;
	//Ellipse(hdc, ballInfo.x, ballInfo.y, ballInfo.x + ballInfo.width, ballInfo.y + ballInfo.height);
	*/
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, prc->right, prc->bottom);
	SelectObject(hdcBuffer, hbmBuffer);

	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmMask = CreateCompatibleBitmap(hdc, ballInfo.width, ballInfo.height);
	SelectObject(hdcMem, hbmMask);

	FillRect(hdcBuffer, prc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	Ellipse(hdcMem, ballInfo.x, ballInfo.y, ballInfo.x + ballInfo.width, ballInfo.y + ballInfo.height);

	BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCINVERT);

	BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCAND);

	//SelectObject(hdcMem, g_hbmBall);
	BitBlt(hdcBuffer, ballInfo.x, ballInfo.y, ballInfo.width, ballInfo.height, hdcMem, 0, 0, SRCINVERT);

	BitBlt(hdc, 0, 0, prc->right, prc->bottom, hdcBuffer, 0, 0, SRCCOPY);

	DeleteDC(hdcMem);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}