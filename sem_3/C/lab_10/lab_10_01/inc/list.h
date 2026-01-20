#ifndef LIST_H__
#define LIST_H__

#include "file_func.h"
#include <stdlib.h>

typedef struct node_t node_t;
typedef int (*func_cmp_ptr)(void *, void *);
typedef void (*print_func_ptr)(void *);
typedef void (*write_func_ptr)(FILE *, void *);

// Создание списка
node_t *create_list(void);

// Создание элемента списка
node_t *create_node(void *value);

// Добавление к конец списка нового элемента
node_t *add_end_list(node_t *head, node_t *node);

// Вставка элемента перед другим в списке
// ЕСЛИ ЧТО-ТО НЕ БУДЕТ ПРОХОДИТЬ В ПАЙПЛАЙНЕ, ТО ОНО РАБОТАТЬ ПРИ BEFORE == NULL НЕ БУДЕТ
void insert(node_t **head, node_t *elem, node_t *before);

// Удаление элемента из списка по значению
node_t *del_by_value_list(node_t *head, void *value, func_cmp_ptr fcmp);

// возвращает указатель на данные из элемента, который расположен в «хвосте» списка
void *pop_back(node_t **head);

node_t *reverse(node_t *head);

void print_list(node_t *head, print_func_ptr print);

void destroy_list(node_t *head);

node_t *fdata_to_list(file_data_t *fdata, size_t data_size);

void write_list(FILE *f, node_t *head, write_func_ptr print);

void sorted_insert(node_t **head, node_t *element, func_cmp_ptr fcmp);

size_t len_list(node_t *head);

node_t *sort(node_t *head, func_cmp_ptr fcmp);

void print_list_index(node_t *head, print_func_ptr print);
node_t *node_by_index_list(node_t *head, size_t ind);
void *data_list(node_t *node);

#endif
