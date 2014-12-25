#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "digraph.h"
#include "set.h"
#include "tools.h"
#include "nfa.h"

#define BUFFER_SIZE 100

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
	result = set_init(&setPossible);
	if (result)
		showError("Malloc for setPossible failed.");
	result = set_init(&setMatch);
	if (result)
		showError("Malloc for setMatch failed.");

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
				if (re[item] != '(' && re[item] != ')')
					if (re[item] == str[i] || re[item] == '.')
						set_add(setMatch, item + 1);
		}
		set_clear(setPossible);

		for (j = 0; j < g->vertices; j++)
			marked[j] = 0;

		for (j = 0; j < setMatch->items; j++)
		{
			item = set_get_value(setMatch, j);
			digraph_dfs(g, marked, item);
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

int recognize_arr(char * str, char * re, digraph_t * g)
{
	int i, j, z;
	int possible[1000], match[1000];
	int pos_ptr, mat_ptr;
	int result = -1;
	int *marked;
	int item, check;

	pos_ptr = 0;
	mat_ptr = 0;

	marked = malloc(g->vertices * sizeof(int));
	for (i = 0; i < g->vertices; i++)
		marked[i] = 0;
	digraph_dfs(g, marked, 0);
	
	for (i = 0; i < g->vertices; i++)
	{
		check = 0;
		if (marked[i])
		{
			for (z = 0; z < pos_ptr; z++)
			{
				if (i == possible[z])
					check = 1;
			}
			if (!check)
				possible[pos_ptr++] = i;
		}
	}

	for (i = 0; i < strlen(str); i++)
	{
		for (j = 0; j < pos_ptr; j++)
		{
			item = possible[j];
			if (item < g->vertices)
				if (re[item] != '(' && re[item] != ')')
					if (re[item] == str[i] || re[item] == '.')
					{
						check = 0;
						for (z = 0; z < mat_ptr; z++)
						{
							if (item+1 == match[z])
								check = 1;
						}
						if (!check)
							match[mat_ptr++] = item + 1;
					}
		}
		pos_ptr = 0;

		for (j = 0; j < g->vertices; j++)
			marked[j] = 0;

		for (j = 0; j < mat_ptr; j++)
		{
			item = match[j];
			digraph_dfs(g, marked, item);
		}

		for (j = 0; j < g->vertices; j++)
		{
			check = 0;
			if (marked[j])
			{
				for (z = 0; z < pos_ptr; z++)
				{
					if (j == possible[z])
						check = 1;
				}
				if (!check)
					possible[pos_ptr++] = j;
			}
		}
		mat_ptr = 0;
	}

	for (i = 0; i < pos_ptr; i++)
	{
		item = possible[i];
		if (item == g->vertices - 1)
		{
			free(marked);
			return 0;
		}
	}
	free(marked);
	return 1;
}

int main(int argc, char** argv)
{
	char regexp[BUFFER_SIZE];
	char regexp_tmp[BUFFER_SIZE];
	char input[1000];
	char buffer[1000];
	int result = -1;
	int ignores_opt, num_opt, set_opt, time_opt, invert_opt, matches_opt;
	digraph_t *graph = NULL;
	clock_t time;
	clock_t allTime;
	int count, matches_all;
	int i, j;

	ignores_opt = 0;
	num_opt = 0;
	set_opt = 0;
	time_opt = 0;
	invert_opt = 0;
	matches_opt = 0;
	matches_all = 0;

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
			case 's':
				set_opt = 1;
				break;
			case 't':
				time_opt = 1;
				break;
			case 'v':
				invert_opt = 1;
				break;
			case 'c':
				matches_opt = 1;
				break;
			case 'h':
				usage();
				break;
			default:
				printf("Wrong argument: %s\n", argv[i]);
				usage();
			}
		}
		else
		{
			strncpy(regexp_tmp, &argv[i][0], BUFFER_SIZE);
			regexp[BUFFER_SIZE - 1] = '\0';
		}
	}

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
	result = digraph_init(&graph, strlen(regexp));
	if (result)
		showError("Malloc for matrix failed.");
	
	create_nfa(graph, regexp);
	allTime = 0;
	count = 1;
	while (!feof(stdin))
	{
		fgets(input, 1000, stdin);
		// exit ^Q
		if (input[0] == 17)
			break;
		i = strlen(input) - 1;
		if (input[i] == '\n') input[i] = '\0';
		time = clock();
		if (ignores_opt)
		{
			strcpy(buffer, input);
			for (i = 0; i < strlen(regexp); i++)
				regexp[i] = tolower(regexp[i]);
			for (i = 0; i < strlen(input); i++)
				input[i] = tolower(input[i]);
		}
		if (set_opt)			
			result = recognize(input, regexp, graph);
		else
			result = recognize_arr(input, regexp, graph);
		time = clock() - time;
		allTime += time;

		if (!matches_opt)
			if (!invert_opt)
			{
			if (!result)
				if (ignores_opt)
					if (!num_opt)
						fprintf(stdout,"%s\n", buffer);
					else
						fprintf(stdout,"%d. %s\n", count, buffer);
				else
					if (!num_opt)
						fprintf(stdout,"%s\n", input);
					else
						fprintf(stdout,"%d. %s\n", count, input);
			}
			else
			{
				if (result)
					if (ignores_opt)
						if (!num_opt)
							fprintf(stdout,"%s\n", buffer);
						else
							fprintf(stdout,"%d. %s\n", count, buffer);
					else
						if (!num_opt)
							fprintf(stdout,"%s\n", input);
						else
							fprintf(stdout,"%d. %s\n", count, input);
			}
		else
			if (!result)
				matches_all++;

		if (num_opt)
			count++;		
	}
	if (matches_opt)
		fprintf(stdout, "Matches: %d \n", matches_all);
	if (time_opt)
		fprintf(stderr, "Time: %d cticks\n", allTime);

	digraph_free(graph);
}