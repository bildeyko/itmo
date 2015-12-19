#include "Action.h"

Action::Action()
{

}

Action::Action(DataLoader* resources, int height, int width)
{
	this->resources = resources;
	this->width = width;
	this->height = height;
	is_premultipliedButtonAlpha = FALSE;
}

void Action::paintBackground(HWND hWnd) {
	paintBackground(hWnd, resources->getHBackgroundImage());
}

void Action::paintBackground(HWND hWnd, HBITMAP bitmap) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	HDC hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, bitmap);
	MaskBlt(hdc, 0, 0, this->width, this->height, hdcMem, 0, 0, resources->getHBackgroundMask1bit(), 0, 0, SRCCOPY);

	//RECT rect;
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	if (is_premultipliedButtonAlpha == FALSE)
		premultipliedAlpha(hdc, resources->getHOrangeButton());


	//OrangeButton *but1 = new OrangeButton(hdc, 494, 504, resources->getHOrangeButton(), resources->getHCenterMask1bit());
	//OrangeButton but1(LEFT_BUTTON, hdc, 494, 504, resources->getHOrangeButton(), resources->getHLeftMask1bit());
	//buttons.push_back(but1);
	OrangeButton but2(CENTER_BUTTON, hdc, 572, 504, resources->getHOrangeButton(), resources->getHCenterMask1bit());
	buttons.push_back(but2);
	//OrangeButton but3(RIGHT_BUTTON, hdc, 650, 504, resources->getHOrangeButton(), resources->getHRightMask1bit());
	//buttons.push_back(but3);

	//but1->set_press(false, hdc, resources->getHOrangeButton());
	//OrangeButton *but2 = new OrangeButton(hdc, 572, 504, resources->getHOrangeButton(), resources->getHCenterMask1bit());
	//OrangeButton *but3 = new OrangeButton(hdc, 650, 504, resources->getHOrangeButton(), resources->getHCenterMask1bit());

	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
}

int Action::which_button(int x, int y)
{
	int button = -1;

	for (vector<OrangeButton>::iterator it = buttons.begin(); it != buttons.end(); it++) {
		if (it->checkPoint(x, y) == true)
			button = it->id;
	}
	return button;
}


HRGN Action::BitMapToHRGN(HBITMAP hBitMap) {
	BITMAP bm;
	HBITMAP hMask = hBitMap;
	GetObject(hMask, sizeof(bm), &bm);
	BYTE * pMaskBits = (BYTE*)bm.bmBits;
	int pixel;
	int xStart = -1;
	HRGN hRgn = 0;

	for (int i = 0; i < bm.bmHeight; i++) {
		for (int j = 0; j < bm.bmWidth; j++) {
			pixel = pMaskBits[i * bm.bmWidthBytes + j];
			if (pixel != 0) {
				if (xStart == -1) xStart = j;
			}
			else {
				if (xStart != -1) {
					if (hRgn == 0)
						hRgn = CreateRectRgn(xStart, bm.bmHeight - i - 1, j, bm.bmHeight - i);
					else
						CombineRgn(hRgn, hRgn, CreateRectRgn(xStart, bm.bmHeight - i - 1, j, bm.bmHeight - i), RGN_OR);
					xStart = -1;
				}
			}

			if (j == bm.bmWidth - 1 && xStart != -1) {
				if (hRgn == 0)
					hRgn = CreateRectRgn(xStart, bm.bmHeight - i - 1, j + 1, bm.bmHeight - i);
				else CombineRgn(hRgn, hRgn, CreateRectRgn(xStart, bm.bmHeight - i - 1, j + 1, bm.bmHeight - i), RGN_OR);
				xStart = -1;
			}
		}
	}
	DeleteObject(hMask);
	return hRgn;
}

void Action::premultipliedAlpha(HDC hdc, HBITMAP hbm)
{
	BITMAP bm;
	BITMAPINFO bmi;

	GetObject(hbm, sizeof(bm), &bm);

	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bm.bmWidth;
	bmi.bmiHeader.biHeight = bm.bmHeight;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;

	DWORD dwBmpSize = ((bm.bmWidth * bmi.bmiHeader.biBitCount + 31) / 32) * 4 * bm.bmHeight;
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	unsigned char *lpbitmap = (unsigned char *)GlobalLock(hDIB);

	GetDIBits(hdc, hbm, 0, (UINT)bm.bmHeight, lpbitmap, &bmi, DIB_RGB_COLORS);

	for (int i = 0; i < dwBmpSize; i = i + 4) {
		unsigned char alpha = lpbitmap[i + 3];
		lpbitmap[i] = lpbitmap[i] * alpha / 0xff;
		lpbitmap[i + 1] = lpbitmap[i + 1] * alpha / 0xff;
		lpbitmap[i + 2] = lpbitmap[i + 2] * alpha / 0xff;
	}

	SetDIBits(hdc, hbm, 0, (UINT)bm.bmHeight, lpbitmap, &bmi, DIB_RGB_COLORS);

	GlobalUnlock(hDIB);
	GlobalFree(hDIB);
}