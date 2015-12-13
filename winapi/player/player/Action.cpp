#include "Action.h"

Action::Action()
{

}

Action::Action(DataLoader* resources, int height, int width)
{
	this->resources = resources;
	this->width = width;
	this->height = height;
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
	DeleteDC(hdcMem);
	EndPaint(hWnd, &ps);
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

	/*WORD wBmpWidth, wBmpHeight;

	// the final region and a temporary region
	HRGN hRgn, hTmpRgn;

	// 24bit pixels from the bitmap
	BYTE *pPixels = Get24BitPixels(hBitMap, &wBmpWidth, &wBmpHeight);
	if (!pPixels) return NULL;

	// create our working region
	hRgn = CreateRectRgn(0, 0, wBmpWidth, wBmpHeight);
	if (!hRgn) { delete pPixels; return NULL; }

	// ---------------------------------------------------------
	// scan the bitmap
	// ---------------------------------------------------------
	DWORD p = 0;
	for (WORD y = 0; y<wBmpHeight; y++)
	{
		for (WORD x = 0; x<wBmpWidth; x++)
		{
			BYTE jRed = pPixels[p + 2];
			BYTE jGreen = pPixels[p + 1];
			BYTE jBlue = pPixels[p + 0];

			if (jRed == 0 && jGreen == 0 && jBlue == 0)
			{
				// remove transparent color from region
				hTmpRgn = CreateRectRgn(x, y, x + 1, y + 1);
				CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				DeleteObject(hTmpRgn);
			}

			// next pixel
			p += 3;
		}
	}

	// release pixels
	delete pPixels;

	// return the region
	return hRgn;*/
}

BYTE* Action::Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight)
{
	// a bitmap object just to get bitmap width and height
	BITMAP bmpBmp;

	// pointer to original bitmap info
	LPBITMAPINFO pbmiInfo;

	// bitmap info will hold the new 24bit bitmap info
	BITMAPINFO bmiInfo;

	// width and height of the bitmap
	WORD wBmpWidth, wBmpHeight;

	// ---------------------------------------------------------
	// get some info from the bitmap
	// ---------------------------------------------------------
	GetObject(pBitmap, sizeof(bmpBmp), &bmpBmp);
	pbmiInfo = (LPBITMAPINFO)&bmpBmp;

	// get width and height
	wBmpWidth = (WORD)pbmiInfo->bmiHeader.biWidth;
	wBmpWidth -= (wBmpWidth % 4);                       // width is 4 byte boundary aligned.
	wBmpHeight = (WORD)pbmiInfo->bmiHeader.biHeight;

	// copy to caller width and height parms
	*pwWidth = wBmpWidth;
	*pwHeight = wBmpHeight;
	// ---------------------------------------------------------

	// allocate width * height * 24bits pixels
	BYTE *pPixels = new BYTE[wBmpWidth*wBmpHeight * 3];
	if (!pPixels) return NULL;

	// get user desktop device context to get pixels from
	HDC hDC = GetWindowDC(NULL);

	// fill desired structure
	bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiInfo.bmiHeader.biWidth = wBmpWidth;
	bmiInfo.bmiHeader.biHeight = -wBmpHeight;
	bmiInfo.bmiHeader.biPlanes = 1;
	bmiInfo.bmiHeader.biBitCount = 24;
	bmiInfo.bmiHeader.biCompression = BI_RGB;
	bmiInfo.bmiHeader.biSizeImage = wBmpWidth*wBmpHeight * 3;
	bmiInfo.bmiHeader.biXPelsPerMeter = 0;
	bmiInfo.bmiHeader.biYPelsPerMeter = 0;
	bmiInfo.bmiHeader.biClrUsed = 0;
	bmiInfo.bmiHeader.biClrImportant = 0;

	// get pixels from the original bitmap converted to 24bits
	int iRes = GetDIBits(hDC, pBitmap, 0, wBmpHeight, (LPVOID)pPixels, &bmiInfo, DIB_RGB_COLORS);

	// release the device context
	ReleaseDC(NULL, hDC);

	// if failed, cancel the operation.
	if (!iRes)
	{
		delete pPixels;
		return NULL;
	};

	// return the pixel array
	return pPixels;
}
