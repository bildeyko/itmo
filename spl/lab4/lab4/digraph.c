#include "digraph.h"
#include "tools.h"
#include <stdlib.h>
/*
Return values:
	0 - without errors;
	1 - malloc for matrix failed.
*/
int digraph_init(digraph_t ** temp, size_t size)
{
	digraph_t *g;
	int i, j;
	g = (digraph_t *)malloc(sizeof(digraph_t));
	g->vertices = size;
	g->edges = 0;
	g->matrix = (char **)malloc(sizeof(char *)*size);
	if (g->matrix == NULL)		
		return 1;

	for (i = 0; i < size; i++)
		g->matrix[i] = (char *)malloc(sizeof(char)*size);

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			g->matrix[i][j] = 0;
	*temp = g;
	return 0;
}

void digraph_free(digraph_t *g)
{
	int i;
	for (i = 0; i < g->vertices; i++)
		free(g->matrix[i]);
	free(g);
}

/*
Return values:
0 - without errors;
1 - wrong source index;
2 - wrong direction index.
*/
int digraph_add_edge(digraph_t *g, unsigned int source, unsigned int dir)
{
	if (source >= g->vertices)
		return 1;
	if (dir >= g->vertices)
		return 2;
	g->matrix[source][dir] = 1;
	g->edges++;
	return 0;
}

void digraph_dfs(digraph_t *g, int *marked, int source)
{
	int i;
	marked[source] = 1;
	for (i = 0; i < g->vertices; i++)
	{
		if (g->matrix[source][i])
			if (!marked[i])
				digraph_dfs(g, marked, i);
	}
}
