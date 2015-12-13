#include "DataLoader.h"

DataLoader::DataLoader(HINSTANCE hInstance)
{
	hBackgroundImage = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_BACKGROUND), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBackgroundMask8bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_BACKGROUND_MASK_8_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBackgroundMask1bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_BACKGROUND_MASK_1_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}

HBITMAP DataLoader::getHBackgroundImage()
{
	return hBackgroundImage;
}

HBITMAP DataLoader::getHBackgroundMask8bit()
{
	return hBackgroundMask8bit;
}

HBITMAP DataLoader::getHBackgroundMask1bit()
{
	return hBackgroundMask1bit;
}