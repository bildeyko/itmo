#include <stdio.h>
#include <time.h>
#include "array.h"
#include "sort.h"
#include "tools.h"

typedef void(*array_sort_ptr)(array_t * arr, comparer_t comp);
extern void sort_gen_asm(array_t * arr, comparer_t comp);
extern void print_array(array_t * arr, size_t size);

#define REPS_d 100001
//#define REPS_d 10

time_t measurementTime(array_sort_ptr arraySort, array_t * arr, unsigned int iterations)
{
	time_t time, allTime;
	int i, j;
	array_t * arrTemp;
	allTime = 0;
	for (i = 0; i < iterations; i++)
	{
		arrTemp = array_create(arr->size);
		if (arrTemp == NULL)
			break;
		for (j = 0; j < arrTemp->size; j++)
			arrTemp->arrayPtr[j] = arr->arrayPtr[j];
		time = clock();
		arraySort(arrTemp, &comparer);
		time = clock() - time;
		allTime += time;
		array_destroy(arrTemp);
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
	curFile = fopen("input2.txt", "r");
	if (curFile == NULL)
	{
		showError("Error with file reading");
		exit(1);
	}
	arr = array_get(curFile);
	if (arr == NULL)
		exit(1);
	arrayFunc = &sort_get;
	printf("Shell sort\n\n", arr->size);
	printf("   Array size: %d\n", arr->size);
	printf("   Reps: %d\n", REPS_d);
	printf("   Array:\n", REPS_d);
	print_array(arr->arrayPtr, arr->size);
	printf("\n   Results:\n", REPS_d);
	resultTime = measurementTime(arrayFunc, arr, REPS_d);
	printf("   C: %d tics\n", resultTime);
	arrayFunc = &sort_gen_asm;
	resultTime = measurementTime(arrayFunc, arr, REPS_d);
	printf("   Asm: %d tics\n", resultTime);
	array_destroy(arr);
	system("pause");
	return 0;
}