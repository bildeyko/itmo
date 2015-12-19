#include "DataLoader.h"

DataLoader::DataLoader(HINSTANCE hInstance)
{
	hBackgroundImage = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_BACKGROUND), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBackgroundMask8bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_BACKGROUND_MASK_8_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hBackgroundMask1bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_BACKGROUND_MASK_1_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hOrangeButton = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_ORANGEBUTTON), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hCenterMask1bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_CENTER_MASK_1_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hLeftMask1bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_LEFT_MASK_1_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hRightMask1bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_RIGHT_MASK_1_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	hCloseMask1bit = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(ID_BM_CLOSE_MASK_1_BIT), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
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

HBITMAP DataLoader::getHOrangeButton()
{
	return hOrangeButton;
}

HBITMAP DataLoader::getHCenterMask1bit()
{
	return hCenterMask1bit;
}

HBITMAP DataLoader::getHLeftMask1bit()
{
	return hLeftMask1bit;
}

HBITMAP DataLoader::getHRightMask1bit()
{
	return hRightMask1bit;
}

HBITMAP DataLoader::getHCloseMask1bit()
{
	return hCloseMask1bit;
}