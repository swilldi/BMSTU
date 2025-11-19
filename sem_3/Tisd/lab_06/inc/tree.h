#ifndef TREE_H__
#define TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "value_t.h"

#define STR_LEN 128

#define FMT_TYPE "%s"
#define FMT      FMT_TYPE" -> "FMT_TYPE";\n"
#define SPACE_FMT "  "FMT
#define HIGHLIGH_FMT FMT_TYPE" [ color=blue, penwidth=3 ];"

typedef struct tree_node tree_node;
typedef void (*ptr_action_t)(tree_node*, void*);
typedef int(*compare_func)(void *a, void *b);
typedef int (*check_value_func)(value_t);

typedef struct
{
    char symbol;
    FILE *f;
} info_struct;

struct tree_node
{
    tree_node *left;
    tree_node *right;

    char value[STR_LEN];
};


// Создание элемента дерева
tree_node* tree_node_create(value_t value);
// Освобождение памяти содержимого элемента
void tree_node_free_content(tree_node *node);
// Освобождение памяти элемента
void tree_node_destroy(tree_node *node, void *arg);

void tree_destroy(tree_node *node);

tree_node *tree_lookup(tree_node *tree, char *str);


// префиксное применене к элементам дерева: +ab
void tree_apply_pre(tree_node *tree, ptr_action_t f, void *arg);
// инфиксное применене к элементам дерева: a+b
void tree_apply_in(tree_node *tree, ptr_action_t f, void *arg);
// постфиксное применене к элементам дерева: ab+
void tree_apply_post(tree_node *tree, ptr_action_t f, void *arg);

// Вставка нового элемента в дерево
tree_node *tree_insert(tree_node *tree, tree_node *node);
// удаление элемента из дерева по значению
tree_node *tree_remove(tree_node *tree, value_t value);

int tree_height(tree_node *tree, int);


int tree_lookup_count(tree_node *tree, char symbol);
void tree_find_by_first_symbol_all(tree_node *tree, node_t **list, char symbol);




void print_dot_null(FILE *f, value_t value, int nullcount);
void print_dot(FILE *f, tree_node *node, void *arg);
void add_highlight_conf(tree_node *node, info_struct *info);
void tree_export_to_dot(FILE *f, tree_node *tree, node_t *list);
void dot_to_png(char *file_name, char *out_name);

#endif
