#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "common_define.h"

typedef struct avl_tree_node avl_tree_node;
typedef void (*avl_tree_apply_func)(avl_tree_node *node, void *param);

// === Выделение и освобождение памяти ===
// Создание дерева
avl_tree_node *avl_tree_create(void);

// выделение памяти для узла дерева
avl_tree_node *avl_tree_node_create(char *value);
// освобождение памяти узла дерева
void avl_tree_node_destroy(avl_tree_node *node, void *param);

// освобождение памяти всего дерева
// void avl_tree_destroy(avl_tree_node *avl_tree, avl_tree_apply_func free_func)
void avl_tree_destroy(avl_tree_node *avl_tree);


// === Приминение ко всем элементам дерева ===
// префиксное приминение функции func ко всем узлам
void avl_tree_apple_pre(avl_tree_node *avl_tree, avl_tree_apply_func func, void *param);
// инфиксное приминение функции func ко всем узлам
void avl_tree_apple_in(avl_tree_node *avl_tree, avl_tree_apply_func func, void *param);
// постфиксное приминение функции func ко всем узлам
void avl_tree_apple_post(avl_tree_node *avl_tree, avl_tree_apply_func func, void *param);

// === Взаимодействие с деревом ===
// Вставка нового узла node
avl_tree_node *avl_tree_insert(avl_tree_node *avl_tree, avl_tree_node *node, compare_func cmp_func);

// Удаление узла со значением value
avl_tree_node *avl_tree_remove(avl_tree_node *avl_tree, char *value, compare_func cmp_func);
// Удаление всех букв по первой букве 
avl_tree_node *avl_tree_remove_by_first_symbol(avl_tree_node *tree, char symbol);

// === Поиск элементов ===
// Поиск узла со значеним value
avl_tree_node *avl_tree_lookup(avl_tree_node *avl_tree, char *value, compare_func cmp_func);
// Поиск родителя узла node
avl_tree_node *avl_tree_lookup_parent(avl_tree_node *avl_tree, avl_tree_node *node, compare_func cmp_func);

// Поиск минимального узал в дереве avl_tree
avl_tree_node *avl_tree_pop_min(avl_tree_node **avl_tree);


// === Доступ к данным ===
void *avl_tree_value(avl_tree_node *node);
avl_tree_node *avl_tree_left_child(avl_tree_node *node);
avl_tree_node *avl_tree_right_child(avl_tree_node *node);
int avl_tree_height(avl_tree_node *node);


// === Балансировка ===
// Изменение состояние балансировки
void avl_tree_set_height(avl_tree_node *node);
// Состояние баналанса
int avl_tree_balance_factor(avl_tree_node *node);
// Левый поворот
avl_tree_node *avl_tree_rotate_right(avl_tree_node *node);
// Правый поворот
avl_tree_node *avl_tree_rotate_left(avl_tree_node *node);
// Балансировка дерева
avl_tree_node *avl_tree_balanace(avl_tree_node *node);


#endif
