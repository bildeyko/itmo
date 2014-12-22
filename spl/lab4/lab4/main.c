#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "digraph.h"
#include "set.h"

#define BUFFER_SIZE 100

int create_nfa(digraph_t * g, char * regexp)
{
	int stack[1000];
	int ptr, lenght;
	int i, lp, or;
	ptr = -1;
	or = 0;
	lenght = strlen(regexp); // а надо ли? 
	
	for (i = 0; i < g->vertices; i++)
	{
		lp = i;
		if (regexp[i] == '(' || regexp[i] == '|')
			stack[++ptr] = i;
		else if (regexp[i] == ')')
		{
			or = stack[ptr--];
			if (regexp[or] == '|')
			{
				lp = stack[ptr--];
				digraph_add_edge(g, lp, or + 1);
				digraph_add_edge(g, or, i);
			}
			else
				lp = or;
		}
		if (i < g->vertices - 1 && regexp[i + 1] == '*')
		{
			digraph_add_edge(g, lp, i + 1);
			digraph_add_edge(g, i + 1, lp);
		}
		if (i < g->vertices - 1 && regexp[i + 1] == '+')
		{
			digraph_add_edge(g, i + 1, lp);
		}
		if (i < g->vertices - 1 && regexp[i + 1] == '?')
		{
			digraph_add_edge(g, lp, i + 1);
		}
		if (regexp[i] == '(' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '?' || regexp[i] == ')') // тут, когда последняя скобка ) по идее будет ошибка выхода за пределы массива, так что надо делать размер +1
			digraph_add_edge(g, i, i + 1);
	}
}

int recognize(char * str, char * re, digraph_t * g)
{
	int i, j;
	int result = -1;
	int *marked;
	set_t *setPossible, *setMatch;
	int item;

	marked = malloc(g->vertices * sizeof(int));
	for (i = 0; i < g->vertices; i++)
		marked[i] = 0;
	digraph_dfs(g, marked, 0);
	set_init(&setPossible);
	set_init(&setMatch);

	/*for (i = 0; i < g->vertices; i++)
	{
		for (j = 0; j < g->vertices; j++)
			printf("%d\t", g->matrix[i][j]);
		printf("\n");
	}
	printf("Marked:\n");
	for (i = 0; i < g->vertices; i++)
	{
		printf("%d\t", marked[i]);
	}*/

	for (i = 0; i < g->vertices; i++)
	{
		if (marked[i])
			set_add(setPossible, i);
	}
	for (i = 0; i < strlen(str); i++)
	{
		for (j = 0; j < setPossible->items; j++)
		{
			item = set_get_value(setPossible, j);
			if (item < g->vertices)
				if (re[item] != '(' && re[item] != ')') //// фикс для работы со строками, которые уже содержат скобки
					if (re[item] == str[i] || re[item] == '.')
						set_add(setMatch, item + 1);
		}
		set_clear(setPossible);

		for (j = 0; j < g->vertices; j++)
			marked[j] = 0;

		for (j = 0; j < setMatch->items; j++)
		{
			item = set_get_value(setMatch, j);
			digraph_dfs(g, marked, item); ////
		}

		for (j = 0; j < g->vertices; j++)
		{
			if (marked[j])
				set_add(setPossible, j);
		}
		set_clear(setMatch);
	}

	for (i = 0; i < setPossible->items; i++)
	{
		item = set_get_value(setPossible, i);
		if (item == g->vertices - 1)
		{
			set_clear(setPossible);
			set_clear(setMatch);
			free(setMatch);
			free(setPossible);
			free(marked);
			return 0;
		}
	}
	set_clear(setPossible);
	set_clear(setMatch);
	free(setMatch);
	free(setPossible);
	free(marked);
	return 1;
}

int main(int argc, char** argv)
{
	char regexp[BUFFER_SIZE];
	char regexp_tmp[BUFFER_SIZE];
	char input[1000];
	//int size = 5;
	int result = -1;
	int *marked;
	int ignores_opt, num_opt;
	digraph_t *graph = NULL;
	clock_t time;
	clock_t allTime;
	int count;
	//set_t *set;

	int i, j;
	ignores_opt = 0;
	num_opt = 0;
	strcpy(regexp, "");
	for (i = 1; i<argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'i':
				ignores_opt = 1;
				break;
			case 'n':
				num_opt = 1;
				break;
			default:
				printf("Wrong argument: %s\n", argv[i]);
				//usage();
			}
		}
		else
		{
			strncpy(regexp_tmp, &argv[i][0], BUFFER_SIZE);
			regexp[BUFFER_SIZE - 1] = '\0';
		}
	}


	//strcpy(regexp, "(.*ab(2c|d1).*)");
	if (regexp_tmp[0] != '^')
	{
		strncat(regexp, ".*", 2);
		strncat(regexp, regexp_tmp, strlen(regexp_tmp));
		strcpy(regexp_tmp, regexp);
	}
	else
	{
		strncat(regexp, regexp_tmp + 1, strlen(regexp_tmp));
		strcpy(regexp_tmp, regexp);
	}
	if (regexp_tmp[strlen(regexp_tmp)-1] != '$')
	{
		strcpy(regexp, regexp_tmp);
		//strncat(regexp, regexp_tmp, strlen(regexp_tmp));
		strncat(regexp, ".*", 2);		
		strcpy(regexp_tmp, regexp);
	}
	else
	{
		strcpy(regexp, regexp_tmp);
		regexp[strlen(regexp) - 1] = '\0';
		strcpy(regexp_tmp, regexp);
	}
	strcpy(regexp, "");
	strncat(regexp, "(", 1);
	strncat(regexp, regexp_tmp, strlen(regexp_tmp));
	strncat(regexp, ")", 1);
	//strcpy(input, "cabd1");
	//strcpy(regexp, "(.*AB((C|D*E)F)*G)");
	//strcpy(regexp, "((a*b|ac)d)");
	result = digraph_init(&graph, strlen(regexp));
	if (result)
		showError("Malloc for matrix failed.");

	/*result = add_edge(graph, 2, 5);
	if (result == 1)
		showError("Wrong source index.");
	if (result == 2)
		showError("Wrong direction index.");

	result = add_edge(graph, 4, 0);*/

	
	create_nfa(graph, regexp);
	//freopen("datebook", "r", stdin);
	allTime = 0;
	count = 1;
	while (!feof(stdin))
	{
		fgets(input, 1000, stdin);
		i = strlen(input) - 1;
		if (input[i] == '\n') input[i] = '\0';
		time = clock();
		result = recognize(input, regexp, graph);
		time = clock() - time;
		allTime += time;		
		if (!result)
			if (!num_opt)
				printf("%s\n", input);
			else
				printf("%d. %s\n", count, input);
		if (num_opt)
			count++;
		
	}
	fprintf(stdout, " Time: %d cticks\n", allTime);
	
	/*for (i = 0; i < graph->vertices; i++)
	{
		for (j = 0; j < graph->vertices; j++)
			printf("%d\t", graph->matrix[i][j]);
		printf("\n");
	}
	marked = malloc(graph->vertices * sizeof(int));
	for (i = 0; i < graph->vertices; i++)
		marked[i] = 0;
	digraph_dfs(graph, marked, 1);

	
	printf("Marked:\n");
	for (i = 0; i < graph->vertices; i++)
	{
		printf("%d\t", marked[i]);		
	}
	printf("\n");*/

	digraph_free(graph);
	//system("pause");
}