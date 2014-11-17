#include "array.h"

// ?? Эта функйия такая должна быть? 
void array_create(array_t * arr, size_t size)
{
	arr->size = size;
	arr->arrayPtr = (int *)malloc(sizeof(int)*size);
	if (arr->arrayPtr == NULL) {
		showError("Malloc for arr.arrayPtr failed.");
	}	
}

array_t * array_get(FILE * file)
{
	size_t size;
	int num;
	array_t * arr;
	int i;
	int * buf;

	fscanf(file, "%d", &size);
	arr = (array_t *)malloc(sizeof(array_t));
	if (arr == NULL) {
		showError("Malloc for arr failed.");
		return NULL;
	}
	arr->arrayPtr = NULL;
	arr->size = NULL;

	array_create(arr, size);
	if (arr->arrayPtr == NULL)
		return NULL;

	for (i = 0; i < arr->size; i++) 
	{
		fscanf(file, "%d", &num);
		arr->arrayPtr[i] = num;
	}

	return arr;
}

void array_destroy(array_t * arr)
{
	free(arr->arrayPtr);
	free(arr);
}