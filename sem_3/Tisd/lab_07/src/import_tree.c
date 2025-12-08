#define GNU_SOURCE_
#include <string.h>
#include <stdio.h>

#include "bin_search_tree.h"
#include "avl_tree.h"
#include "compare_func.h"

// TODO сделать чтение универсальным
tree_node *file_to_tree(FILE *f)
{
    tree_node *tree = tree_create();

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        tree = tree_insert(tree, tree_node_create(str), cmp_str);
        s = getline(&str, &len, f);
    }

    return tree;
}

// TODO сделать чтение универсальным
avl_tree_node *file_to_avl_tree(FILE *f)
{
    avl_tree_node *tree = avl_tree_create();

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        tree = avl_tree_insert(tree, avl_tree_node_create(str), cmp_str);
        s = getline(&str, &len, f);
    }

    return tree;
}
