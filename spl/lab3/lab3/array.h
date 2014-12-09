#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

typedef struct {
	int * arrayPtr;
	size_t size;
} array_t;

array_t * array_create(size_t size);
array_t * array_get(FILE * file);
void array_destroy(array_t * arr);

#endif