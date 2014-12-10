#ifndef bmpStruct_H
#define bmpStruct_H

#pragma pack(push, 2)
typedef struct {
	char signature[2];
	unsigned int fileSize;
	char empty1[2];
	char empty2[2];
	unsigned int address;

	int headerLength;
	int width;
	int height;
	short int numberOfColorPlanes;
	short int pixelSize;
	int method;
	int arrayLength;
	int hRes;
	int vRes;
	int numberOfColors;
	int numberOfPrColors;
} bmpFileStruct;
#pragma pack(pop)

typedef struct {
	int width;
	int height;
	int size;
	int factWidth;
} imageInfoStruct;

#endif