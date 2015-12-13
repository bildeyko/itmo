#pragma once

#include <Windows.h>
#include "DataLoader.h"

class Action
{
	DataLoader* resources;
	void paintBackground(HWND hWnd, HBITMAP bitmap);
	BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight);
	int height;
	int width;
public:
	Action();
	Action(DataLoader* resources, int height, int width);
	HRGN BitMapToHRGN(HBITMAP hBitMap);
	void paintBackground(HWND hWnd);
};