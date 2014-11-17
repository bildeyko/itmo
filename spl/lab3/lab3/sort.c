#include "sort.h"

int comparer(int a, int b)
{
	if (a == b)
		return 0;
	if (a > b)
		return 1;
	else
		return -1;
}

void sort_get(array_t * arr, comparer_t comp)
{
	int k, i, j, temp;

	for (k = arr->size / 2; k > 0; k /= 2)
	{
		for (i = k; i < arr->size; i++)
		{
			temp = arr->arrayPtr[i];
			for (j = i; j >= k; j -= k)
			{
				if (comp(temp, arr->arrayPtr[j - k]) == -1)
					arr->arrayPtr[j] = arr->arrayPtr[j - k];
				else
					break;
			}
			arr->arrayPtr[j] = temp;
		}
	}
}