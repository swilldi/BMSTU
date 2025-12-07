#ifndef BIN_SEARCH_TREE_H__
#define BIN_SEARCH_TREE_H__

typedef struct tree_node tree_node;
typedef void (*tree_apply_func)(tree_node *node, void *param);

typedef void (*free_func)(void *);
typedef int (*compare_func)(void *, void *);

// === Выделение и освобождение памяти ===
// выделение памяти для узла дерева
tree_node *tree_node_create(void *value);
// освобождение памяти узла дерева
void tree_node_destroy(tree_node *node, free_func func);
// освобождение памяти всего дерева
void tree_destroy(tree_node *tree, free_func func);

// === Приминение ко всем элементам дерева ===
void tree_apple_pre(tree_node *tree, tree_apply_func func, void *param);
void tree_apple_in(tree_node *tree, tree_apply_func func, void *param);
void tree_apple_post(tree_node *tree, tree_apply_func func, void *param);

// === Взаимодействие с деревом ===
tree_node *tree_insert(tree_node *tree, tree_node *node, compare_func cmp_func);
tree_node *tree_remove(tree_node *tree, void *value, compare_func cmp_func);

// === Поиск элементов ===
// Поиск узла со значеним value
tree_node *tree_lookup(tree_node *tree, void *value, compare_func cmp_func);
tree_node *tree_lookup_parent(tree_node *tree, tree_node *node, compare_func cmp_func);
tree_node *tree_pop_min(tree_node **tree);

#endif
