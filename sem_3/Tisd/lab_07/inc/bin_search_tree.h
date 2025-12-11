#ifndef BIN_SEARCH_BIN_TREE_H__
#define BIN_SEARCH_BIN_TREE_H__

#include "common_define.h"

typedef struct bin_tree_node bin_tree_node;
typedef void (*bin_tree_apply_func)(bin_tree_node *node, void *param);

// === Выделение и освобождение памяти ===
// Создание дерева
bin_tree_node *bin_tree_create(void);
// выделение памяти для узла дерева
bin_tree_node *bin_tree_node_create(char *value);
// освобождение памяти узла дерева
void bin_tree_node_destroy(bin_tree_node *node, void *param);
// освобождение памяти всего дерева
void bin_tree_destroy(bin_tree_node *tree);

// === Приминение ко всем элементам дерева ===
void bin_tree_apple_pre(bin_tree_node *tree, bin_tree_apply_func func, void *param);
void bin_tree_apple_in(bin_tree_node *tree, bin_tree_apply_func func, void *param);
void bin_tree_apple_post(bin_tree_node *tree, bin_tree_apply_func func, void *param);

// === Взаимодействие с деревом ===
bin_tree_node *bin_tree_insert(bin_tree_node *tree, bin_tree_node *node, compare_func cmp_func);
bin_tree_node *bin_tree_remove(bin_tree_node *tree, char *value, compare_func cmp_func);
bin_tree_node *bin_tree_remove_by_first_symbol(bin_tree_node *tree, char symbol);

// === Поиск элементов ===
// Поиск узла со значеним value
bin_tree_node *bin_tree_lookup(bin_tree_node *tree, char *value, compare_func cmp_func);
bin_tree_node *bin_tree_lookup_parent(bin_tree_node *tree, bin_tree_node *node, compare_func cmp_func);
bin_tree_node *bin_tree_pop_min(bin_tree_node **tree);


// === Доступ к данным ===
void *bin_tree_value(bin_tree_node *node);
bin_tree_node *bin_tree_left_child(bin_tree_node *node);
bin_tree_node *bin_tree_right_child(bin_tree_node *node);

int bin_tree_lookup_cmp_count(bin_tree_node *tree, char *value);
double bin_tree_avg_cmp(bin_tree_node *tree, int runs);


#endif
