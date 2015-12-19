#pragma once
#pragma comment(lib, "Msimg32.lib")

#include <Windows.h>

class OrangeButton
{
	HBITMAP background;
	int height;
	int width;
	int x;
	int y;
	bool pressed;
	BYTE* maskBits;
	int maskHeight;
	int maskWidth;
public:
	OrangeButton(int id, HDC hdc, int x, int y, HBITMAP view, HBITMAP mask);
	bool isPressed();
	void set_press(bool status, HDC hdc, HBITMAP view);
	bool checkPoint(int x, int y);
	int id;
};