#ifndef LIST_H__
#define LIST_H__

#include "exit_code.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t node_t;
typedef int (*func_cmp_ptr)(void *, void *);
typedef void (*print_func_ptr)(void *);
typedef void (*write_func_ptr)(FILE *, void *);

// Создание списка
node_t *create_list(void);

// Создание элемента списка
node_t *create_node(int value);

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

void write_list(FILE *f, node_t *head, write_func_ptr print);

void sorted_insert(node_t **head, node_t *element, func_cmp_ptr fcmp);

size_t len_list(node_t *head);

node_t *sort(node_t *head, func_cmp_ptr fcmp);

void print_list_index(node_t *head, print_func_ptr print);
node_t *node_by_index_list(node_t *head, size_t ind);
int data_list(node_t *node);

bool is_prime_num(int num);
int next_prime_num(int num);
node_t *num_to_list(int num);
error list_to_num(node_t *head, int *num);
node_t *mul_list_num(node_t *num_1, node_t *num_2);
node_t *sqr_list_num(node_t *num);
error div_list_num(node_t *lnum_1, node_t *lnum_2, node_t **div_num);

#endif
