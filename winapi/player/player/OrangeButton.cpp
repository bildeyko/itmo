#include "OrangeButton.h"
#include <vector>

OrangeButton::OrangeButton(int id, HDC hdc,  int x, int y, HBITMAP view, HBITMAP mask)
{
	pressed = false;
	BITMAP bm;
	HDC hdcMem = CreateCompatibleDC(hdc);
	GetObject(view, sizeof(bm), &bm);

	this->height = bm.bmHeight;
	this->width = bm.bmWidth;
	this->x = x;
	this->y = y;
	this->id = id;

	background = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(hdcMem, background);	

	BitBlt(hdcMem, 0, 0, width, height, hdc, x, y, SRCCOPY);
	DeleteDC(hdcMem);

	GetObject(mask, sizeof(bm), &bm);
	maskBits = (BYTE*)bm.bmBits;
	maskHeight = bm.bmHeight;
	maskWidth = bm.bmWidth;
}

bool OrangeButton::isPressed()
{
	return pressed;
}

void OrangeButton::set_press(bool status, HDC hdc, HBITMAP view)
{
	pressed = status;
	HDC hdcMem1 = CreateCompatibleDC(hdc);
	SelectObject(hdcMem1, background);

	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP background2 = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(hdcBuffer, background2);

	BitBlt(hdcBuffer, 0, 0, width, height, hdcMem1, 0, 0, SRCCOPY);

	if (status == true)
	{
		HDC hdcMem2 = CreateCompatibleDC(hdc);
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
		SelectObject(hdcMem2, view);
		AlphaBlend(hdcBuffer, 0, 0, width, height, hdcMem2, 0, 0, width, height, blend);
		DeleteDC(hdcMem2);
	}

	BitBlt(hdc, x, y, width, height, hdcBuffer, 0, 0, SRCCOPY);

	DeleteObject(background2);
	DeleteDC(hdcMem1);
	DeleteDC(hdcBuffer);
}

bool OrangeButton::checkPoint(int x, int y) {
	int alignment = 4 - (maskWidth+1) / 8 % 4;
	alignment = (alignment == 4) ? 0 : alignment;
	/*int a1 = maskHeight - y;
	int a2 = maskWidth / 8 + alignment;
	int a3 = x / 8;
	int coord = a1 * a2 + a3 + 64;
	int res = maskBits[coord];
	return (maskBits[coord] >> (7 - (x % 8))) % 2 == 1;
	return (bits[(windowHeight - y)  * (windowWidth / 8 + alignment) + x / 8] >> (7 - (x % 8))) % 2 && 1;*/

	/*int a1 = maskHeight - y;
	int a2 = a1 * (maskWidth/8+ alignment/8);
	int coord = a2 + x/8;
	int res = maskBits[coord];
	return (maskBits[coord] >> (7 - (x % 8))) % 2 == 1;*/
	int res = maskBits[(maskHeight - y) * (maskWidth / 8 + alignment) + x / 8];
	return (maskBits[(maskHeight - y)  * (maskWidth / 8 + alignment) + x / 8] >> (7 - (x % 8))) % 2 && 1;
}