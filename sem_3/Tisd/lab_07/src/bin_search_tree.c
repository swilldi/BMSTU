#include <stdlib.h>
#include <string.h>

#include "bin_search_tree.h"

struct tree_node
{
    // хранимые данные
    char value[STR_LEN];

    // Дочерние ноды
    tree_node *left;
    tree_node *right;
};

// === Выделение и освобождение памяти ===
// Создание дерева
tree_node *tree_create(void)
{
    return NULL;
}

// выделение памяти для узла дерева
tree_node *tree_node_create(char *value)
{
    tree_node *node = malloc(sizeof(tree_node));
    if (node)
    {
        node->left = node->right = NULL;
        strcpy(node->value, value);
    }
    return node;
}
// освобождение памяти узла дерева
void tree_node_destroy(tree_node *node, void *param)
{   
    (void)param;
    free(node);
}

// освобождение памяти всего дерева
// void tree_destroy(tree_node *tree, tree_apply_func free_func)
void tree_destroy(tree_node *tree)
{
    if (!tree)
        return;

    // Освобождение памяти узлов дерева
    tree_apple_post(tree, tree_node_destroy, NULL);
}


// === Приминение ко всем элементам дерева ===
// префиксное приминение функции func ко всем узлам
void tree_apple_pre(tree_node *tree, tree_apply_func func, void *param)
{
    if (!tree)
        return;

    func(tree, param);
    tree_apple_pre(tree->left, func, param);
    tree_apple_pre(tree->right, func, param);
}
// инфиксное приминение функции func ко всем узлам
void tree_apple_in(tree_node *tree, tree_apply_func func, void *param)
{
    if (!tree)
        return;

    tree_apple_in(tree->left, func, param);
    func(tree, param);
    tree_apple_in(tree->right, func, param);
}
// постфиксное приминение функции func ко всем узлам
void tree_apple_post(tree_node *tree, tree_apply_func func, void *param)
{
    if (!tree)
        return;
    
    tree_apple_post(tree->left, func, param);
    tree_apple_post(tree->right, func, param);
    func(tree, param);
}

// === Взаимодействие с деревом ===
// Вставка нового узла node
tree_node *tree_insert(tree_node *tree, tree_node *node, compare_func cmp_func)
{
    if (!tree)
        return node;

    int cmp = cmp_func(tree->value, node->value);
    if (cmp > 0)
        tree->left = tree_insert(tree->left, node, cmp_func);
    else if (cmp < 0)
        tree->right = tree_insert(tree->right, node, cmp_func);

    return tree;
}

// Удаление узла со значением value
tree_node *tree_remove(tree_node *tree, char *value, compare_func cmp_func)
{
    if (!tree)
        return NULL;

    int cmp = cmp_func(tree->value, value);
    if (cmp > 0)
        tree->left = tree_remove(tree->left, value, cmp_func);
    else if (cmp < 0)
        tree->right = tree_remove(tree->right, value, cmp_func);
    else
    {
        if (tree->left == NULL)
        {
            tree_node *temp_node = tree->right;
            free(tree);
            return temp_node;
        }
        else if (tree->right == NULL)
        {
            tree_node *temp_node = tree->left;
            free(tree);
            return temp_node;
        }
        else
        {
            tree_node *min_node = tree_pop_min(&tree->right);
            min_node->left = tree->left;
            min_node->right = tree->right;
            free(tree);
            return min_node;
        }
    }

    return tree;
}

// === Поиск элементов ===
// Поиск узла со значеним value
tree_node *tree_lookup(tree_node *tree, char *value, compare_func cmp_func)
{
    int cmp;

    while (tree != NULL)
    {
        cmp = cmp_func(tree->value, value);
        if (cmp > 0)
            tree = tree->left;
        else if (cmp < 0)
            tree = tree->right;
        else
            return tree;
    }

    return NULL;
}
// Поиск родителя узла node
tree_node *tree_lookup_parent(tree_node *tree, tree_node *node, compare_func cmp_func)
{
    int cmp;

    while (tree != NULL)
    {
        cmp = cmp_func(tree->value, node->value);
        if (cmp > 0)
            tree = tree->left;
        else if (cmp < 0)
            tree = tree->right;
        else if (tree->left == node || tree->right == node)
            return tree;
        else
            return NULL;
    }

    return NULL;
}

// Поиск минимального узал в дереве tree
tree_node *tree_pop_min(tree_node **tree)
{
    tree_node *cur = *tree, *prev = NULL;
    while (cur->left)
    {
        prev = cur;
        cur = cur->left;
    }
    
    if (!prev)
        *tree = NULL;
    else
        prev->left = NULL;
    
    return cur;
}


// === Доступ к данным ===
void *tree_value(tree_node *node)
{
    return node->value;
}

tree_node *tree_left_child(tree_node *node)
{
    return node->left;
}

tree_node *tree_right_child(tree_node *node)
{
    return node->right;
}
