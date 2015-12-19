#pragma once

#include <Windows.h>
#include <vector>
#include "DataLoader.h"
#include "OrangeButton.h"

#define CENTER_BUTTON 100
#define LEFT_BUTTON 101
#define RIGHT_BUTTON 102

using namespace std;

class Action
{
	DataLoader* resources;
	void paintBackground(HWND hWnd, HBITMAP bitmap);
	BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight);
	int height;
	int width;
	BOOL is_premultipliedButtonAlpha;
	vector<OrangeButton> buttons;
public:
	Action();
	Action(DataLoader* resources, int height, int width);
	HRGN BitMapToHRGN(HBITMAP hBitMap);
	void premultipliedAlpha(HDC hdc, HBITMAP hbm);
	void paintBackground(HWND hWnd);
	int which_button(int x, int y);
};