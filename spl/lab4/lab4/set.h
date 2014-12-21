#ifndef SET_H
#define SET_H

typedef struct item_t set_item_t;

struct item_t{
	int value;
	set_item_t *next;
};

typedef struct {
	unsigned int items;
	set_item_t *head;
} set_t;

int set_init(set_t ** set);
int set_add(set_t * set, int value);
int set_get_value(set_t *set, int index);
void set_clear(set_t *set);
#endif