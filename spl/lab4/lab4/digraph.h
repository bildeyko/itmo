#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdio.h>

typedef struct {
	char **matrix;
	size_t vertices;
} digraph_t;

digraph_t * digraph_init(size_t size);
#endif