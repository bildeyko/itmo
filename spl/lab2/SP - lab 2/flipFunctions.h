#ifndef flipFunctions_H
#define flipFunctions_H

#include "bmpStruct.h"

void flipImageC(unsigned char * imageArray, imageInfoStruct imageInfo);
void flipImageC_memcpy(unsigned char * imageArray, imageInfoStruct imageInfo);
void flipImageAsm(unsigned char * imageArray, imageInfoStruct imageInfo);
void flipImageMMX(unsigned char * imageArray, imageInfoStruct imageInfo);

#endif