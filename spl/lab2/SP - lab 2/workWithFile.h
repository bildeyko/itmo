#include "bmpStruct.h"

#ifndef workWithFile_H
#define workWithFile_H

imageInfoStruct loadImageFile(char * path, bmpFileStruct * file, unsigned char ** imageArray);
int safeImageFile(char * fileName, char * prefix, bmpFileStruct * file, unsigned char ** imageArray);

#endif