#pragma once

#include <Windows.h>
#include "resource.h"

class DataLoader
{
	HBITMAP hBackgroundImage, hBackgroundMask8bit, hBackgroundMask1bit, hOrangeButton,
		hCenterMask1bit, hLeftMask1bit, hRightMask1bit, hCloseMask1bit;

public:
	DataLoader(HINSTANCE hInstance);
	HBITMAP getHBackgroundImage();
	HBITMAP getHBackgroundMask8bit();
	HBITMAP getHBackgroundMask1bit();
	HBITMAP getHOrangeButton();
	HBITMAP getHCenterMask1bit();
	HBITMAP getHLeftMask1bit();
	HBITMAP getHRightMask1bit();
	HBITMAP getHCloseMask1bit();
};