#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "array_t.h"
#include <stdbool.h>

// #define value_t char*



// префиксное применене к элементам дерева: +ab
void tree_apply_pre(tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    tree_apply_pre(tree->left, f, arg);
    tree_apply_pre(tree->right, f, arg);
}

// инфиксное применене к элементам дерева: a+b
void tree_apply_in(tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    tree_apply_in(tree->left, f, arg);
    f(tree, arg);
    tree_apply_in(tree->right, f, arg);
}

// постфиксное применене к элементам дерева: ab+
void tree_apply_post(tree_node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    tree_apply_post(tree->left, f, arg);
    tree_apply_post(tree->right, f, arg);
    f(tree, arg);
}

// Вставка нового элемента в дерево
tree_node *tree_insert(tree_node *tree, tree_node *node)
{
    if (!tree)
        return node;
    
    int cmp = strcmp(tree->value, node->value);
    if (cmp > 0)
    {
        tree->left = tree_insert(tree->left, node);
    }
    else if (cmp < 0)
    {
        tree->right = tree_insert(tree->right, node);
    }

    return tree;
}

tree_node *tree_lookup(tree_node *tree, char *str)
{
    int cmp;
    if (!tree)
        return NULL;

    while (tree != NULL)
    {
        cmp = strcmp(str, tree->value);
        if (cmp == 0)
            return tree;
        else if (cmp > 0)
            tree = tree->right;
        else if (cmp < 0)
            tree = tree->left;
    }

    return NULL;
}

tree_node* min_right_subtree(tree_node *tree)
{
    tree_node *cur = tree->right;
    while (cur != NULL && cur->left != NULL)
        cur = cur->left;
    return cur;
}

// Удаление элемента из дерева по значеню
tree_node *tree_remove(tree_node *tree, value_t value)
{
    if (!tree)
        return tree;
    
    int cmp = strcmp(tree->value, value);

    if (cmp > 0)
    {
        tree->left = tree_remove(tree->left, value);
    }
    else if (cmp < 0)
    {
        tree->right = tree_remove(tree->right, value);
    }
    else
    {
        if (tree->left == NULL)
        {
            tree_node *temp = tree->right;
            free(tree);
            return temp;
        }
        else if (tree->right == NULL)
        {
            tree_node *temp = tree->left;
            free(tree);
            return temp;
        }
        else
        {
            tree_node *temp = min_right_subtree(tree);
            tree_node_free_content(tree);
            strcpy(tree->value, temp->value);
            tree->right = tree_remove(tree->right, tree->value);
        }
    }

    return tree;
}

// Создание элемента дерева
tree_node* tree_node_create(value_t value)
{
    tree_node *node = malloc(sizeof(tree_node));
    if (node)
    {
        strcpy(node->value, value);
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void tree_destroy(tree_node *tree)
{
    tree_apply_post(tree, tree_node_destroy, NULL);
}

// Освобождение памяти содержимого элемента
void tree_node_free_content(tree_node *node)
{
    (void)node;
    return;
}

// Освобождение памяти элемента
void tree_node_destroy(tree_node *node, void *arg)
{
    (void)arg;
    tree_node_free_content(node);
    free(node);
}

int tree_lookup_count(tree_node *tree, char symbol)
{
    static int count = 0;

    if (!tree)
        return count;
    
    if (tree->value[0] == symbol)
        count++;
    
    tree_lookup_count(tree->left, symbol);
    tree_lookup_count(tree->right, symbol);

    return count;
}

void tree_find_by_first_symbol_all(tree_node *tree, node_t **list, char symbol)
{
    if (!tree)
        return;

    if (tree->value[0] == symbol)
    {
        node_t *tmp_node = create_node(tree->value);
        *list = add_node(*list, tmp_node);
        tree_find_by_first_symbol_all(tree->left, list, symbol);
        tree_find_by_first_symbol_all(tree->right, list, symbol);
    }
    else if (tree->value[0] > symbol)
    {
        tree_find_by_first_symbol_all(tree->left, list, symbol);
    }
    else if (tree->value[0] < symbol)
    {
        tree_find_by_first_symbol_all(tree->right, list, symbol);
    }
    
}



void tree_add_to_list(tree_node *node, void *arg)
{
    node_t *list = arg;
    node_t *tmp_node = create_node(node->value);
    add_node(list, tmp_node);
}


void tree_add_to_arr(tree_node *node, void *arg)
{
    array_t *arr = arg;
    arr->data[arr->len] = node->value;
    arr->len += 1;
}

void tree_to_sort_array(tree_node *tree, array_t *arr)
{
    tree_apply_in(tree, tree_add_to_arr, arr);
}



void print_dot_null(FILE *f, value_t value, int nullcount)
{
    // fprintf(f, "  null%d;\n", nullcount);
    fprintf(f, "  null%d [label=\"\", shape=none, width=0, height=0 ];\n", nullcount);
    fprintf(f, "  "FMT_TYPE" -> null%d;\n", value, nullcount);
}

void print_dot(FILE *f, tree_node *node, void *arg)
{
    static int nullcount = 0;
    node_t *list = arg;

    if (node->left)
    {
        if (list_contain(list, node->left->value))
            fprintf(f, "  "HIGHLIGH_FMT"\n", node->left->value);

        fprintf(f, SPACE_FMT, node->value, node->left->value);
        print_dot(f, node->left, arg);
    }
    else
    {
        print_dot_null(f, node->value, nullcount++);
    }

    if (node->right)
    {
        if (list_contain(list, node->right->value))
            fprintf(f, "  "HIGHLIGH_FMT"\n", node->right->value);

        fprintf(f, SPACE_FMT, node->value, node->right->value);
        print_dot(f, node->right, arg);
    }
    else
    {
        print_dot_null(f, node->value, nullcount++);
    }
   
}

int tree_height(tree_node *tree, int h)
{
    if (tree == NULL)
        return h - 1;
    int left_height = tree_height(tree->left, h + 1);
    int right_height = tree_height(tree->right, h + 1);

    return left_height > right_height ? left_height : right_height;
}


void tree_export_to_dot(FILE *f, tree_node *tree, node_t *list)
{
    info_struct *info = NULL;
    fprintf(f, "digraph tree {\n");

    if (list_contain(list, tree->value))
            fprintf(f, "  "HIGHLIGH_FMT"\n", tree->value);
    
    if (!tree)
    {
        fprintf(f, "\n");
    }
    else if (!tree->left && !tree->right)
    {
        fprintf(f, "  %s;\n", tree->value);
    }
    else
    {
        print_dot(f, tree, list);
    }
    
    fprintf(f, "}\n");
    free(info);
}


void dot_to_png(char *file_name, char *out_name)
{
    char cmd_str[128];

    sprintf(cmd_str, "dot -Tpng -o %s %s > /dev/null", out_name, file_name);
    system(cmd_str);
}
