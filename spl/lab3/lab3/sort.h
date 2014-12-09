#ifndef SORT_H
#define SORT_H

#include "array.h"

typedef int(*comparer_t)(int * a, int * b);
int comparer(int a, int b);
void sort_get(array_t * arr, comparer_t comp);

#endif