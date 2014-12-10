#include <string.h>
#include "bmpStruct.h"
#include "flipFunctions.h"

void flipImageC(unsigned char * imageArray, imageInfoStruct imageInfo)
{
	int i, j, k;
	int endHeight, height, width;
	//unsigned char *temp[4];
	unsigned char temp;
	height = imageInfo.height;
	width = imageInfo.factWidth;

	height--;
	endHeight = (height / 2);
	for (i = 0; i <= endHeight; i++) {
		for (j = 0; j<width; j ++) {
			/*memcpy(temp, &imageArray[(height - i)*width + j], 4);
			memcpy(&imageArray[(height - i)*width + j], &imageArray[i*width + j], 4);
			memcpy(&imageArray[i*width + j], temp, 4);*/
			temp = imageArray[(height - i)*width + j];
			imageArray[(height - i)*width + j] = imageArray[i*width + j];
			imageArray[i*width + j] = temp;
		}
	}
}

void flipImageC_memcpy(unsigned char * imageArray, imageInfoStruct imageInfo)
{
	int i, j;
	int endHeight, height, width;
	unsigned char *temp[4];
	height = imageInfo.height;
	width = imageInfo.factWidth;

	height--;
	endHeight = (height / 2);
	for (i = 0; i <= endHeight; i++) {
		for (j = 0; j<width; j = j + 4) {
			memcpy(temp, &imageArray[(height - i)*width + j], 4);
			memcpy(&imageArray[(height - i)*width + j], &imageArray[i*width + j], 4);
			memcpy(&imageArray[i*width + j], temp, 4);
		}
	}
}

void flipImageAsm(unsigned char * imageArray, imageInfoStruct imageInfo)
{
	int w;
	int h;
	int endHeight;

	__asm {
		lea ebx, imageInfo
		mov eax, [ebx]imageInfo.factWidth
		mov w, eax

		mov eax, [ebx]imageInfo.height
		dec eax;
		mov h, eax

		shr eax, 1
		mov endHeight, eax

		mov esi, imageArray
		mov edi, imageArray

		xor ecx, ecx
	downloop :
		; calculating offset in an image array for line
		; in the upper half of the image.
		mov eax, h
		sub eax, ecx
		mul w

		; calculating destination
		push edi
		add edi, eax

		push ecx
		xor ecx, ecx
	uploop :
		mov edx, [edi] ; save the data from a destination
		cld
		movsd

		sub esi, 4
		mov [esi], edx ; replace the data in a source with saved data from a destination
		add esi, 4

		add ecx, 4
		cmp ecx, w
		jl uploop

		pop ecx
		pop edi
		inc ecx
		cmp ecx, endHeight
		jbe downloop; <=
	}
}

void flipImageMMX(unsigned char * imageArray, imageInfoStruct imageInfo)
{
	int w;
	int h;
	int endHeight;

	__asm {
		lea ebx, imageInfo
		mov eax, [ebx]imageInfo.factWidth
		mov w, eax

		mov eax, [ebx]imageInfo.height
		dec eax;
		mov h, eax

		shr eax, 1
		mov endHeight, eax

		mov esi, imageArray
		mov edi, imageArray

		xor ecx, ecx
	downloop :
		; calculating offset in an image array for line
		; in the upper half of the image.
		mov eax, h
		sub eax, ecx
		mul w

		; calculating destination
		push edi
		add edi, eax

		push ecx
		xor ecx, ecx
	uploop :
		movd mm0, [edi]
		movd mm1, [esi]
		movd [edi], mm1
		movd [esi], mm0

		add esi, 4
		add edi, 4

		add ecx, 4
		cmp ecx, w
		jl uploop

		pop ecx
		pop edi
		inc ecx
		cmp ecx, endHeight
		jbe downloop; <=

		emms
	}
}