#include <stdio.h>
#include <string.h>

#include "digraph.h"

int main(int argc, char** argv)
{
	char regexp[30];
	int size = 5;
	int result = -1;
	digraph_t *graph = NULL;

	int i, j;

	strcpy(regexp, "(abc)");
	result = digraph_init(&graph, size);
	if (result)
		showError("Malloc for matrix failed.");

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%d", graph->matrix[i][j]);
		printf("\n");
	}

	digraph_free(graph);
	system("pause");
}