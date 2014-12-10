#include "digraph.h"
#include "tools.h"

digraph_t * digraph_init(size_t size)
{
	digraph_t *g;
	int i, j;
	g = (digraph_t *)malloc(sizeof(digraph_t));
	g->vertices = size;
	g->matrix = (char **)malloc(sizeof(char *)*size);
	if (g->matrix == NULL)
	{
		showError("Malloc for g->matrix failed.");
		return NULL;
	}

	for (i = 0; i < size; i++)
		g->matrix[i] = (char *)malloc(sizeof(char)*size);

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			g->matrix[i][j] = -1;
	return g;
}

void digraph_free(digraph_t *g)
{
	int i;
	for (i = 0; i < g->vertices; i++)
		free(g->matrix[i]);
	free(g);
}