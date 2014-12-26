#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <stdio.h>

typedef struct {
	char **matrix;
	size_t vertices;
	size_t edges;
} digraph_t;

int digraph_init(digraph_t ** g, size_t size);
int digraph_add_edge(digraph_t *g, unsigned int source, unsigned int dir);
void digraph_dfs(digraph_t *g, int *marked, int source);
void digraph_free(digraph_t *g);
#endif