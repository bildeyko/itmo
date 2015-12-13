#pragma once

#include <Windows.h>
#include "resource.h"

class DataLoader
{
	HBITMAP hBackgroundImage, hBackgroundMask8bit, hBackgroundMask1bit;

public:
	DataLoader(HINSTANCE hInstance);
	HBITMAP getHBackgroundImage();
	HBITMAP getHBackgroundMask8bit();
	HBITMAP getHBackgroundMask1bit();
};