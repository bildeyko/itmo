#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdio.h>

typedef struct {
	char **matrix;
	size_t vertices;
} digraph_t;

int digraph_init(digraph_t ** g, size_t size);
#endif