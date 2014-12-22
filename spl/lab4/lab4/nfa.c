#include "digraph.h"
#include "nfa.h"

int create_nfa(digraph_t * g, char * regexp)
{
	int stack[1000];
	int ptr = -1;
	int i, lp, or;

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
				add_error(digraph_add_edge(g, lp, or + 1));
				add_error(digraph_add_edge(g, or, i));
			}
			else
				lp = or;
		}
		if (i < g->vertices - 1 && regexp[i + 1] == '*')
		{
			add_error(digraph_add_edge(g, lp, i + 1));
			add_error(digraph_add_edge(g, i + 1, lp));
		}
		if (i < g->vertices - 1 && regexp[i + 1] == '+')
		{
			add_error(digraph_add_edge(g, i + 1, lp));
		}
		if (i < g->vertices - 1 && regexp[i + 1] == '?')
		{
			add_error(digraph_add_edge(g, lp, i + 1));
		}
		if (regexp[i] == '(' || regexp[i] == '*' || regexp[i] == '+' || regexp[i] == '?' || regexp[i] == ')')
			digraph_add_edge(g, i, i + 1);
	}
}