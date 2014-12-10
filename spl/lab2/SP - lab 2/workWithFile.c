#include <stdio.h>
#include <direct.h>
#include <malloc.h>
#include "bmpStruct.h"
#include "workWithFile.h"
#include "tools.h"
#include "constants.h"

imageInfoStruct loadImageFile(char * path, bmpFileStruct * file, unsigned char ** imageArray)
{
	FILE *curFile;
	imageInfoStruct imageInfo;

	curFile = fopen(path, "rb");
	if (curFile == NULL)
	{
		showError("Error with file reading");
		exit(1);
	}
	fread(file, sizeof(*file), 1, curFile);
	if (checkStruct(file))
		exit(1);
	imageInfo.height = file->height;
	imageInfo.width = file->width;
	imageInfo.size = file->arrayLength;
	imageInfo.factWidth = imageInfo.size / imageInfo.height;

	*imageArray = (unsigned char*)malloc(sizeof(unsigned char *)*imageInfo.size);
	if (*imageArray == NULL)
		exit(8);

	fseek(curFile, file->address, SEEK_SET);
	fread(*imageArray, 4, file->arrayLength / 4, curFile);
	fclose(curFile);

	return imageInfo;
}

int checkStruct(bmpFileStruct *bmpFile)
{
	if (bmpFile->signature[0] != 'B' || bmpFile->signature[1] != 'M')
	{
		showError("It isn't a BMP file.");
		return 1;
	}
	if (bmpFile->pixelSize != 24)
	{
		showError("It isn't a 24-bit BMP file.");
		return 1;
	}
	return 0;
}

int safeImageFile(char * fileName, char * suffix, bmpFileStruct * file, unsigned char ** imageArray)
{
	FILE *newFile;
	int result;
	char newName[100];
	char dirName[100];

	strcpy(newName, "");
	strcpy(dirName, "results");

	mkdir(dirName);
	strncat(newName, dirName, strlen(dirName));
	strncat(newName, "/", 1);
	strncat(newName, fileName, BUFFER_SIZE);
	strncat(newName, suffix, strlen(suffix));
	strncat(newName, ".bmp", 4);

	newFile = fopen(&newName, "wb");
	if (newFile == NULL)
	{
		showError("Error with file creating");
		return 1;
	}

	fwrite(file, sizeof(*file), 1, newFile);
	fseek(newFile, file->address, SEEK_SET);
	fwrite(*imageArray, 4, file->arrayLength / 4, newFile);
	fclose(newFile);

	return 0;
}