#include "array.h"

array_t * array_create(size_t size)
{
	array_t *arr;
	arr = (array_t *)malloc(sizeof(array_t));
	if (arr == NULL) {
		showError("Malloc for arr failed.");
		return NULL;
	}
	arr->arrayPtr = (int *)malloc(sizeof(int)*size);
	arr->size = size;
	if (arr->arrayPtr == NULL) {
		showError("Malloc for arr.arrayPtr failed.");
		return NULL;
	}
	return arr;
}

array_t * array_get(FILE * file)
{
	size_t size;
	int num, i, *buf;
	array_t * arr, temp;
	fscanf(file, "%d", &size);
	arr = array_create(size);
	if (arr == NULL)
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