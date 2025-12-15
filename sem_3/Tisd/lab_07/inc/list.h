#ifndef LIST_H__
#define LIST_H__

#include <stdlib.h>
#include <stdbool.h>
#include "hash_type.h"

typedef struct node_t node_t;
typedef int (*func_cmp_ptr)(void *, void *);
typedef int (*list_apply_func)(node_t*, void*);

// Создание списка
node_t *list_create(void);
// Создание элемента списка
node_t *list_create_node(void *value);
void list_destroy(node_t *head);
// Добавление к конец списка нового элемента
node_t *list_add_end(node_t *head, node_t *node);
// Удаление элемента из списка по значению
node_t *list_del_by_valuet(node_t *head, void *value, func_cmp_ptr fcmp);
void list_print(node_t *head, hash_func_ptr hash);
void *list_data(node_t *node);
size_t len_list(node_t *head);
bool list_contain(node_t *node, char *value);
size_t list_node_size(void);
int list_apply(node_t *list, list_apply_func func, void *param);
node_t *list_next(node_t *node);

#endif
