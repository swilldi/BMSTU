#define _GNU_SOURCE
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "tree.h"
#include "list.h"


node_t *create_node(value_t value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->value = strdup(value);
        node->next = NULL;
    }
    
    return node;
}

node_t* add_node(node_t *head, node_t *new_node)
{
    if (!head)
        return new_node;

    node_t *cur = head;
    while (cur->next)
        cur = cur->next;

    cur->next = new_node;

    return head;
}

bool list_contain(node_t *head, value_t value)
{
    for (; head; head = head->next)
    {
        if (strcmp(head->value, value) == 0)
            return true;
    }
    return false;
}

int len_list(node_t *head)
{
    int count = 0;

    for (; head; head = head->next)
        count++;
    
    return count;
}

void destroy_list(node_t *head)
{
    node_t *next;
    while (head)
    {
        next = head->next;
        free(head);
        free(head->value);
        head = next;
    }
}


void print_list(node_t *head)
{
    for (; head; head = head->next)
        printf("%s\n", head->value);
}


