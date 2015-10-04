#include <Windows.h>
#include <stdlib.h>
#include <tchar.h>
#include <math.h>

#define MAX_LOADSTRING 100
#define SINBUTTON_ID 1
#define COSBUTTON_ID 2
#define X1TEXT_ID 3 
#define X2TEXT_ID 4 
#define LINEWIDTH_ID 5
#define BUFLENGTH 10

#define PI 3.141592653589793238464
#define TWOPI (2*PI)
#define PISIZE 100 // px

HINSTANCE hInst;

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				ChoosingColor(HWND hWnd, COLORREF &col);
int					GenPointArray(POINT ** arr, int x1, int x2, int width, int height, int leftOffset,
								  double(*func)(double));
void				drawFunc(HDC hdc, int width, int height, POINT * points, int lenght, int lineWidth, COLORREF color);
void				drawAxesText(HDC hdc, int width, int height);
void				drawAxes(HDC hdc, int width, int height);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) 
{
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
		900, 710,
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

void ChoosingColor(HWND hWnd, COLORREF &col) 
{
	CHOOSECOLOR cc;
	COLORREF arrCol[16] = { 0 };
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;	
	cc.lpCustColors = arrCol;
	cc.rgbResult = col;
	cc.Flags = CC_RGBINIT;
	if (ChooseColor(&cc)) {
		col = cc.rgbResult;
	}
}

int GenPointArray(POINT ** arr, int x1, int x2, int width, int height, int leftOffset,
				  double(*func)(double))
{
	int num, pxs;
	int realX1, realX2;
	
	if (x1 >= x2)
		return -1;

	realX1 = (x1 / PI) * PISIZE;
	realX2 = (x2 / PI) * PISIZE;
	pxs = abs(realX1) + abs(realX2);

	*arr = (POINT*)malloc(sizeof(POINT)*pxs);
	for (int i = 0; i < pxs; i++)
	{
		(*arr)[i].x = realX1 + width / 2 + i - leftOffset;
		(*arr)[i].y = (int)(height / 2 * (1 - func(TWOPI * (i + realX1) / (2 * PISIZE))));
	}
	return pxs;
}

void drawFunc(HDC hdc, int width, int height, POINT * points, int lenght, int lineWidth,  COLORREF color) {
	HPEN hPen, hOldPen;
	hPen = CreatePen(PS_SOLID, 1, color);
	hOldPen = (HPEN)SelectObject(hdc, hPen);	
	for (int i = 0; i < lineWidth; i++) {
		for (int j = 0; j < lenght; j++)
			points[j].x++;
		Polyline(hdc, points, lenght);
	}
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);	
}

void drawAxesText(HDC hdc, int width, int height)
{
	TextOut(hdc, width - 10, height / 2 - 20, L"X", 1);
	TextOut(hdc, width / 2 + 5, 5, L"Y", 1);
	TextOut(hdc, width / 2 - 8, 5, L"1", 1);
	TextOut(hdc, width / 2 - 13, height - 14, L"-1", 2);

	TextOut(hdc, width / 2 + PISIZE - 2, height / 2 + 5, L"Pi", 2);
	TextOut(hdc, width / 2 + 2 * PISIZE - 8, height / 2 + 5, L"2*Pi", 4);
	TextOut(hdc, width / 2 - PISIZE - 6, height / 2 + 5, L"-Pi", 3);
	TextOut(hdc, width / 2 - 2 * PISIZE - 13, height / 2 + 5, L"-2*Pi", 5);
}

void drawAxes(HDC hdc, int width, int height)
{
	// x-axis
	MoveToEx(hdc, 0, height / 2, (LPPOINT)NULL);
	LineTo(hdc, width, height / 2);
	// x arrow
	MoveToEx(hdc, width - 8, height / 2 - 4, (LPPOINT)NULL);
	LineTo(hdc, width, height / 2);
	MoveToEx(hdc, width - 8, height / 2 + 4, (LPPOINT)NULL);
	LineTo(hdc, width, height / 2);
	// y-axis	
	MoveToEx(hdc, width / 2, 0, (LPPOINT)NULL);
	LineTo(hdc, width / 2, height);
	// y arrow
	MoveToEx(hdc, width / 2, 0, (LPPOINT)NULL);
	LineTo(hdc, width / 2 - 8, 4);
	MoveToEx(hdc, width / 2, 0, (LPPOINT)NULL);
	LineTo(hdc, width / 2 + 8, 4);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	COLORREF color, newColor;
	int wmId, wmEvent;

	static COLORREF sinColor = RGB(255 * rand(), 255 * rand(), 255 * rand());
	static COLORREF cosColor = RGB(255 * rand(), 255 * rand(), 255 * rand());
	TCHAR buf[BUFLENGTH];

	TCHAR x1Lbl[] = L"X1";
	TCHAR x2Lbl[] = L"X2";
	TCHAR widthLbl[] = L"Line width";
	TCHAR colorsLbl[] = L"Colors";

	static int x1;
	static int x2;
	static int lineWidth;
	BOOL fError;

	switch (message) {
	case WM_CREATE:
		HWND hStart, hEnd, hWidth, hColorSin, hColorCos;
		hStart = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 85, 10, 50, 20, hWnd, (HMENU)X1TEXT_ID, hInst, 0);
		hEnd = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER, 85, 40, 50, 20, hWnd, (HMENU)X2TEXT_ID, hInst, 0);
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
		HDC hdc;
		PAINTSTRUCT ps;
		WINDOWINFO hwndInfo;
		POINT * arr;
		int height, width, lenght;
		double(*trig)(double);

		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 10, 12, x1Lbl, _tcslen(x1Lbl));
		TextOut(hdc, 10, 42, x2Lbl, _tcslen(x2Lbl));
		TextOut(hdc, 10, 72, widthLbl, _tcslen(widthLbl));
		TextOut(hdc, 52, 102, colorsLbl, _tcslen(colorsLbl));

		ZeroMemory(&hwndInfo, sizeof(WINDOWINFO));
		hwndInfo.cbSize = sizeof(WINDOWINFO);
		GetWindowInfo(hWnd, &hwndInfo);
		width = hwndInfo.rcClient.right - hwndInfo.rcClient.left;
		height = hwndInfo.rcClient.bottom - hwndInfo.rcClient.top;

		trig = sin;
		lenght = GenPointArray(&arr, x1, x2, width, height, (lineWidth-1)/2, trig);
		if (lenght == -1)
		{
			EndPaint(hWnd, &ps);
			break;
		}
		drawAxesText(hdc, width, height);
		drawFunc(hdc, width, height, arr, lenght, lineWidth, sinColor);
		free(arr);

		trig = cos;
		lenght = GenPointArray(&arr, x1, x2, width, height, (lineWidth - 1) / 2, trig);
		drawFunc(hdc, width, height, arr, lenght, lineWidth, cosColor);
		free(arr);

		drawAxes(hdc, width, height);

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
			case SINBUTTON_ID:
				ChoosingColor(hWnd, sinColor);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case COSBUTTON_ID:
				ChoosingColor(hWnd, cosColor);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case X1TEXT_ID:
				if (wmEvent == EN_UPDATE)
					x1 = GetDlgItemInt(hWnd, X1TEXT_ID, &fError, TRUE);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case X2TEXT_ID:
				if (wmEvent == EN_UPDATE)
					x2 = GetDlgItemInt(hWnd, X2TEXT_ID, &fError, TRUE);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			case LINEWIDTH_ID:
				if (wmEvent == EN_UPDATE)
					lineWidth = GetDlgItemInt(hWnd, LINEWIDTH_ID, &fError, FALSE);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			default:
				break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
