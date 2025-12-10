#include "list.h"
#include "common_define.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "exit_code.h"
#include "hash_type.h"

struct node_t
{
    char data[STR_LEN];
    node_t *next;
};

// Создание списка
node_t *list_create(void)
{
    return NULL;
}

// Создание элемента списка
node_t *list_create_node(void *value)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        strcpy(node->data, value);
        node->next = NULL;
    }
    return node;
}

void list_destroy(node_t *head)
{
    if (!head)
        return;

    node_t *cur = head, *next;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

// Добавление к конец списка нового элемента
node_t *list_add_end(node_t *head, node_t *node)
{
    if (!head)
        return node;

    node_t *cur = head;
    while (cur->next)
        cur = cur->next;

    cur->next = node;

    return head;
}

// Удаление элемента из списка по значению
node_t *list_del_by_valuet(node_t *head, void *value, func_cmp_ptr fcmp)
{
    // пустой списко
    if (head == NULL)
        return NULL;

    node_t *cur = head, *prev = NULL, *del = NULL;
    while (cur)
    {
        if (fcmp(cur->data, value) == 0)
        {
            del = cur;
            if (prev)
                prev->next = cur = cur->next;
            else
                head = cur = cur->next;

            free(del);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }

    return head;
}

void list_print(node_t *head)
{
    while (head)
    {
        printf("%s (%lld)", head->data, get_str_hash(head->data));

        if (head->next)
            printf(" -> ");
        else
            printf("\n");

        head = head->next;
    }
}


void *list_data(node_t *node)
{
    return node->data;
}

node_t *list_next(node_t *node)
{
    return node->next;
}

size_t len_list(node_t *head)
{
    size_t count = 0;
    while (head)
    {
        head = head->next;
        count += 1;
    }
    return count;
}


bool list_contain(node_t *node, char *value)
{
    while (node)
    {
        if (strcmp(node->data, value) == 0)
            return true;

        node = node->next;
    }

    return false;
}

size_t list_node_size(void)
{
    return sizeof(node_t);
}

int list_apply(node_t *head, list_apply_func func, void *param)
{
    int rc;
    node_t *cur = head;
    while (cur)
    {
        rc = func(cur, param);
        if (rc != OK)
            return rc;

        cur = cur->next;
    }

    return OK;
}
