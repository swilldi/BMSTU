#ifndef LIST_H__
#define LIST_H__
#include <stdbool.h>

#include "value_t.h"

typedef struct node_t node_t;
struct node_t
{
    value_t value;
    node_t *next;
};

node_t *create_node(value_t value);

node_t* add_node(node_t *head, node_t *new_node);

bool list_contain(node_t *head, value_t value);

int len_list(node_t *head);

void destroy_list(node_t *head);
void print_list(node_t *head);

#endif
