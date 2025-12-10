#include <stdlib.h>
#include <string.h>

#include "compare_func.h"
#include "bin_search_tree.h"

struct bin_tree_node
{
    // хранимые данные
    char value[STR_LEN];

    // Дочерние ноды
    bin_tree_node *left;
    bin_tree_node *right;
};

// === Выделение и освобождение памяти ===
// Создание дерева
bin_tree_node *bin_tree_create(void)
{
    return NULL;
}

// выделение памяти для узла дерева
bin_tree_node *bin_tree_node_create(char *value)
{
    bin_tree_node *node = malloc(sizeof(bin_tree_node));
    if (node)
    {
        node->left = node->right = NULL;
        strcpy(node->value, value);
    }
    return node;
}
// освобождение памяти узла дерева
void bin_tree_node_destroy(bin_tree_node *node, void *param)
{   
    (void)param;
    free(node);
}

// освобождение памяти всего дерева
// void bin_tree_destroy(bin_tree_node *tree, bin_tree_apply_func free_func)
void bin_tree_destroy(bin_tree_node *tree)
{
    if (!tree)
        return;

    // Освобождение памяти узлов дерева
    bin_tree_apple_post(tree, bin_tree_node_destroy, NULL);
}


// === Приминение ко всем элементам дерева ===
// префиксное приминение функции func ко всем узлам
void bin_tree_apple_pre(bin_tree_node *tree, bin_tree_apply_func func, void *param)
{
    if (!tree)
        return;

    func(tree, param);
    bin_tree_apple_pre(tree->left, func, param);
    bin_tree_apple_pre(tree->right, func, param);
}
// инфиксное приминение функции func ко всем узлам
void bin_tree_apple_in(bin_tree_node *tree, bin_tree_apply_func func, void *param)
{
    if (!tree)
        return;

    bin_tree_apple_in(tree->left, func, param);
    func(tree, param);
    bin_tree_apple_in(tree->right, func, param);
}
// постфиксное приминение функции func ко всем узлам
void bin_tree_apple_post(bin_tree_node *tree, bin_tree_apply_func func, void *param)
{
    if (!tree)
        return;
    
    bin_tree_apple_post(tree->left, func, param);
    bin_tree_apple_post(tree->right, func, param);
    func(tree, param);
}

// === Взаимодействие с деревом ===
// Вставка нового узла node
bin_tree_node *bin_tree_insert(bin_tree_node *tree, bin_tree_node *node, compare_func cmp_func)
{
    if (!tree)
        return node;

    int cmp = cmp_func(tree->value, node->value);
    if (cmp > 0)
        tree->left = bin_tree_insert(tree->left, node, cmp_func);
    else if (cmp < 0)
        tree->right = bin_tree_insert(tree->right, node, cmp_func);

    return tree;
}

// Удаление узла со значением value
bin_tree_node *bin_tree_remove(bin_tree_node *tree, char *value, compare_func cmp_func)
{
    if (!tree)
        return NULL;

    int cmp = cmp_func(tree->value, value);
    if (cmp > 0)
        tree->left = bin_tree_remove(tree->left, value, cmp_func);
    else if (cmp < 0)
        tree->right = bin_tree_remove(tree->right, value, cmp_func);
    else
    {
        if (tree->left == NULL)
        {
            bin_tree_node *temp_node = tree->right;
            free(tree);
            return temp_node;
        }
        else if (tree->right == NULL)
        {
            bin_tree_node *temp_node = tree->left;
            free(tree);
            return temp_node;
        }
        else
        {
            bin_tree_node *min_node = bin_tree_pop_min(&tree->right);
            min_node->left = tree->left;
            min_node->right = tree->right;
            free(tree);
            return min_node;
        }
    }

    return tree;
}

// Удаление всех букв по первой букве 
bin_tree_node *bin_tree_remove_by_first_symbol(bin_tree_node *tree, char symbol)
{
    if (!tree)
        return NULL;
    
    tree->left = bin_tree_remove_by_first_symbol(tree->left, symbol);
    tree->right = bin_tree_remove_by_first_symbol(tree->right, symbol);

    if (tree->value[0] == symbol)
        tree = bin_tree_remove(tree, tree->value, cmp_str);

    return tree;
}

// === Поиск элементов ===
// Поиск узла со значеним value
bin_tree_node *bin_tree_lookup(bin_tree_node *tree, char *value, compare_func cmp_func)
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
bin_tree_node *bin_tree_lookup_parent(bin_tree_node *tree, bin_tree_node *node, compare_func cmp_func)
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
bin_tree_node *bin_tree_pop_min(bin_tree_node **tree)
{
    bin_tree_node *cur = *tree, *prev = NULL;
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
void *bin_tree_value(bin_tree_node *node)
{
    return node->value;
}

bin_tree_node *bin_tree_left_child(bin_tree_node *node)
{
    return node->left;
}

bin_tree_node *bin_tree_right_child(bin_tree_node *node)
{
    return node->right;
}
