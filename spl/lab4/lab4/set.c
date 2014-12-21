#include "set.h"
#include <stdlib.h>
/*
Return values:
0 - without errors;
1 - malloc for set failed.
*/
int set_init(set_t ** set)
{
	set_t *s;
	s = malloc(sizeof(set_t));
	if (s == NULL)
		return 1;
	s->head = NULL;
	s->items = 0;
	*set = s;
	return 0;
}

int set_add(set_t * set, int value)
{
	set_item_t *newItem;
	set_item_t *current;

	newItem = malloc(sizeof(set_item_t));
	newItem->value = value;
	newItem->next = NULL;

	if (set->head == NULL)
	{
		set->head = newItem;
		set->items++;
	}
	else
	{
		current = set->head;
		if (current->value > newItem->value)
		{
			newItem->next = set->head;
			newItem->next->next = NULL;
			set->head = newItem;
			set->items++;
			return 0;
		}
		if (current->value == newItem->value)
			return 0;
		while (1)
		{			
			if (current->next == NULL)
			{
				current->next = newItem;
				set->items++;
				break;
			}
			if (current->next->value > newItem->value)
			{
				newItem->next = current->next;
				current->next = newItem;
				set->items++;
				break;
			}
			current = current->next;
		}
	}
	return 0;
}

int set_get_value(set_t *set,int index)
{
	set_item_t *current;
	int count = 0;
	current = set->head;
	if (index == 0)
		return current->value;
	while (count < index)
	{
		current = current->next;
		count++;
	}
	return current->value;
}

void set_clear(set_t *set)
{
	set_item_t *current;
	set_item_t *next;
	if (set->head == NULL) // !!!!!!!!!!!!!!!!!!!!!!!!!! cabc - падало
		return;
	current = set->head;
	next = current->next;
	set->head = NULL;
	while (1)
	{
		free(current);
		set->items--;
		if (next == NULL)
			break;
		current = next;
		next = next->next;
	}
	//free(current);
	//set->items--;
}