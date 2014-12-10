#include <stdio.h>
#include <string.h>

#include "digraph.h"

int main(int argc, char** argv)
{
	char regexp[30];
	int size = 5;
	digraph_t *graph;

	int i, j;

	strcpy(regexp, "(abc)");
	graph = digraph_init(5);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%d", graph->matrix[i][j]);
		printf("\n");
	}

	digraph_free(graph);
	system("pause");
}