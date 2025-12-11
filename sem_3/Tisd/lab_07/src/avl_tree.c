#include <stdlib.h>
#include <string.h>

#include "avl_tree.h"
#include "compare_func.h"

struct avl_tree_node
{
    // хранимые данные
    char value[STR_LEN];

    // Дочерние ноды
    avl_tree_node *left;
    avl_tree_node *right;

    // Парамет сбалансированности
    int height;
};

// === Выделение и освобождение памяти ===
// Создание дерева
avl_tree_node *avl_tree_create(void)
{
    return NULL;
}

// выделение памяти для узла дерева
avl_tree_node *avl_tree_node_create(char *value)
{
    avl_tree_node *node = malloc(sizeof(avl_tree_node));
    if (node)
    {
        node->left = node->right = NULL;
        node->height = 0;
        strcpy(node->value, value);
    }
    return node;
}
// освобождение памяти узла дерева
void avl_tree_node_destroy(avl_tree_node *node, void *param)
{   
    (void)param;
    free(node);
}

// void avl_tree_free_node_content(avl_tree_node *node, void *param)
// {   
//     (void)param;
//     free(node->value);
// }

// освобождение памяти всего дерева
// void avl_tree_destroy(avl_tree_node *avl_tree, avl_tree_apply_func free_func)
void avl_tree_destroy(avl_tree_node *avl_tree)
{
    if (!avl_tree)
        return;

    // // // Очищение содержимого дерева
    // // avl_tree_apple_post(avl_tree, avl_tree_free_node_content, NULL);
    // Освобождение памяти узлов дерева
    avl_tree_apple_post(avl_tree, avl_tree_node_destroy, NULL);
}


// === Приминение ко всем элементам дерева ===
// префиксное приминение функции func ко всем узлам
void avl_tree_apple_pre(avl_tree_node *avl_tree, avl_tree_apply_func func, void *param)
{
    if (!avl_tree)
        return;

    func(avl_tree, param);
    avl_tree_apple_pre(avl_tree->left, func, param);
    avl_tree_apple_pre(avl_tree->right, func, param);
}
// инфиксное приминение функции func ко всем узлам
void avl_tree_apple_in(avl_tree_node *avl_tree, avl_tree_apply_func func, void *param)
{
    if (!avl_tree)
        return;

    avl_tree_apple_in(avl_tree->left, func, param);
    func(avl_tree, param);
    avl_tree_apple_in(avl_tree->right, func, param);
}
// постфиксное приминение функции func ко всем узлам
void avl_tree_apple_post(avl_tree_node *avl_tree, avl_tree_apply_func func, void *param)
{
    if (!avl_tree)
        return;
    
    avl_tree_apple_post(avl_tree->left, func, param);
    avl_tree_apple_post(avl_tree->right, func, param);
    func(avl_tree, param);
}

// === Взаимодействие с деревом ===
// Вставка нового узла node
avl_tree_node *avl_tree_insert(avl_tree_node *avl_tree, avl_tree_node *node, compare_func cmp_func)
{
    if (!avl_tree)
        return node;

    int cmp = cmp_func(avl_tree->value, node->value);
    if (cmp > 0)
    {
        avl_tree->left = avl_tree_insert(avl_tree->left, node, cmp_func);
        avl_tree = avl_tree_balanace(avl_tree);
    }
    else if (cmp < 0)
    {
        avl_tree->right = avl_tree_insert(avl_tree->right, node, cmp_func);
        avl_tree = avl_tree_balanace(avl_tree);
    }
    return avl_tree;
}

// Удаление узла со значением value
avl_tree_node *avl_tree_remove(avl_tree_node *avl_tree, char *value, compare_func cmp_func)
{
    if (!avl_tree)
        return NULL;

    int cmp = cmp_func(avl_tree->value, value);
    if (cmp > 0)
        avl_tree->left = avl_tree_remove(avl_tree->left, value, cmp_func);
    else if (cmp < 0)
        avl_tree->right = avl_tree_remove(avl_tree->right, value, cmp_func);
    else
    {
        if (avl_tree->left == NULL)
        {
            avl_tree_node *temp_node = avl_tree->right;
            free(avl_tree);
            avl_tree = temp_node;
        }
        else if (avl_tree->right == NULL)
        {
            avl_tree_node *temp_node = avl_tree->left;
            free(avl_tree);
            avl_tree = temp_node;
        }
        else
        {
            avl_tree_node *min_node = avl_tree_pop_min(&avl_tree->right);
            min_node->left = avl_tree->left;
            min_node->right = avl_tree->right;
            free(avl_tree);
            avl_tree =  min_node;
        }
    }

    avl_tree = avl_tree_balanace(avl_tree);

    return avl_tree;
}

// Удаление всех букв по первой букве 
avl_tree_node *avl_tree_remove_by_first_symbol(avl_tree_node *tree, char symbol)
{
    if (!tree)
        return NULL;
    
    tree->left = avl_tree_remove_by_first_symbol(tree->left, symbol);
    tree->right = avl_tree_remove_by_first_symbol(tree->right, symbol);

    if (tree->value[0] == symbol)
        tree = avl_tree_remove(tree, tree->value, cmp_str);

    return tree;
}

// === Поиск элементов ===
// Поиск узла со значеним value
avl_tree_node *avl_tree_lookup(avl_tree_node *avl_tree, char *value, compare_func cmp_func)
{
    int cmp;

    while (avl_tree != NULL)
    {
        cmp = cmp_func(avl_tree->value, value);
        if (cmp > 0)
            avl_tree = avl_tree->left;
        else if (cmp < 0)
            avl_tree = avl_tree->right;
        else
            return avl_tree;
    }

    return NULL;
}

// Подсчет количества сравнений при поиске одного элемента
int avl_tree_lookup_cmp_count(avl_tree_node *avl_tree, char *value)
{
    int cmp;
    int cmp_count = 0;

    while (avl_tree != NULL)
    {
        cmp = cmp_str(avl_tree->value, value);
        cmp_count++;

        if (cmp > 0)
            avl_tree = avl_tree->left;
        else if (cmp < 0)
            avl_tree = avl_tree->right;
        else
            break;
    }

    return cmp_count;
}

typedef struct
{
    avl_tree_node *root;
    long long total_cmp;
    int elem_count;
} avl_tree_cmp_ctx;

static void avl_tree_collect_cmp(avl_tree_node *node, void *param)
{
    avl_tree_cmp_ctx *ctx = param;
    ctx->total_cmp += avl_tree_lookup_cmp_count(ctx->root, node->value);
    ctx->elem_count++;
}

// Подсчет среднего количества сравнений для всех элементов дерева (один прогон)
double avl_tree_avg_cmp_single_run(avl_tree_node *avl_tree)
{
    if (!avl_tree)
        return 0.0;

    avl_tree_cmp_ctx ctx;
    ctx.root = avl_tree;
    ctx.total_cmp = 0;
    ctx.elem_count = 0;

    avl_tree_apple_in(avl_tree, avl_tree_collect_cmp, &ctx);

    if (ctx.elem_count == 0)
        return 0.0;

    return (double)ctx.total_cmp / ctx.elem_count;
}

// Усреднение по нескольким прогонам
double avl_tree_avg_cmp(avl_tree_node *avl_tree, int runs)
{
    if (!avl_tree || runs <= 0)
        return 0.0;

    double sum = 0.0;

    for (int i = 0; i < runs; i++)
        sum += avl_tree_avg_cmp_single_run(avl_tree);

    return sum / runs;
}

// Поиск родителя узла node
avl_tree_node *avl_tree_lookup_parent(avl_tree_node *avl_tree, avl_tree_node *node, compare_func cmp_func)
{
    int cmp;

    while (avl_tree != NULL)
    {
        cmp = cmp_func(avl_tree->value, node->value);
        if (cmp > 0)
            avl_tree = avl_tree->left;
        else if (cmp < 0)
            avl_tree = avl_tree->right;
        else if (avl_tree->left == node || avl_tree->right == node)
            return avl_tree;
        else
            return NULL;
    }

    return NULL;
}

// Поиск минимального узал в дереве avl_tree
avl_tree_node *avl_tree_pop_min(avl_tree_node **avl_tree)
{
    avl_tree_node *cur = *avl_tree, *prev = NULL;
    while (cur->left)
    {
        prev = cur;
        cur = cur->left;
    }
    
    if (!prev)
        *avl_tree = NULL;
    else
        prev->left = NULL;
    
    return cur;
}


// === Доступ к данным ===
void *avl_tree_value(avl_tree_node *node)
{
    return node->value;
}

avl_tree_node *avl_tree_left_child(avl_tree_node *node)
{
    return node->left;
}

avl_tree_node *avl_tree_right_child(avl_tree_node *node)
{
    return node->right;
}

int avl_tree_height(avl_tree_node *node)
{
    return node ? node->height : -1;
}

// === Балансировка ===
// Изменение состояние балансировки
void avl_tree_set_height(avl_tree_node *node)
{
    int lh = avl_tree_height((node->left));;
    int rh = avl_tree_height((node->right));

    node->height = (lh > rh ? lh : rh) + 1;
}

// Состояние баналанса
int avl_tree_balance_factor(avl_tree_node *node)
{
    return avl_tree_height(node->right) - avl_tree_height(node->left);
}

// Левый поворот
avl_tree_node *avl_tree_rotate_right(avl_tree_node *node)
{
    avl_tree_node *temp_node = node->left;
    node->left = temp_node->right;
    temp_node->right = node;
    avl_tree_set_height(node);
    avl_tree_set_height(temp_node);
    return temp_node;   
}
// Правый поворот
avl_tree_node *avl_tree_rotate_left(avl_tree_node *node)
{
    avl_tree_node *temp_node = node->right;
    node->right = temp_node->left;
    temp_node->left = node;
    avl_tree_set_height(node);
    avl_tree_set_height(temp_node);
    return temp_node;
}

avl_tree_node *avl_tree_balanace(avl_tree_node *node)
{
    if (!node)
        return NULL;

    avl_tree_set_height(node);

    // расбалансированно справа
    if (avl_tree_balance_factor(node) > 1)
    {
        if (avl_tree_balance_factor(node->right) < 0)
            node->right = avl_tree_rotate_right(node->right);
        
        node = avl_tree_rotate_left(node);
    }

    // расбалансирована слева
    if (avl_tree_balance_factor(node) < -1)
    {
        if (avl_tree_balance_factor(node->left) > 0)
            node->left = avl_tree_rotate_left(node->left);
        
        node = avl_tree_rotate_right(node);
    }

    // дерево сбалансированно 
    return node;
}
