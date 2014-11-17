#include <stdio.h>
#include <time.h>
#include "array.h"
#include "sort.h"
#include "tools.h"

typedef void(*array_sort_ptr)(array_t * arr, comparer_t comp);

time_t measurementTime(array_sort_ptr arraySort, array_t * arr, unsigned int iterations)
{
	time_t time, allTime;
	int i, j;
	array_t * arrTemp;
	allTime = 0;
	printf("%d\n", sizeof(comparer_t));
	for (i = 0; i < iterations; i++)
	{
		arrTemp = (array_t *)malloc(sizeof(array_t));
		array_create(arrTemp, arr->size);
		for (j = 0; j < arrTemp->size; j++)
		{
			arrTemp->arrayPtr[j] = arr->arrayPtr[j];
		}

		/*printf("%d_before - ", i);
		print_array(arrTemp->arrayPtr, arrTemp->size);
		printf("\n");*/

		time = clock();
		//arraySort(arrTemp, &comparer);
		sort_gen_asm(arrTemp, &comparer);
		time = clock() - time;
		allTime += time;

		/*printf("%d_after - ", i);
		print_array(arrTemp->arrayPtr, arrTemp->size);
		printf("\n");*/

		//array_destroy(arrTemp);
	}

	return allTime;
}

int main(int argc, char** argv)
{
	FILE *curFile;
	array_t * arr;
	array_sort_ptr arrayFunc;
	int i;
	time_t resultTime;

	curFile = fopen("input.txt", "r");
	if (curFile == NULL)
	{
		showError("Error with file reading");
		exit(1);
	}

	arr = array_get(curFile);
	arrayFunc = &sort_get;
	resultTime = measurementTime(arrayFunc, arr, 100);
	printf("%d\n", resultTime);
	print_array(arr->arrayPtr, arr->size);
	array_destroy(arr);
	system("pause");
	return 0;
}