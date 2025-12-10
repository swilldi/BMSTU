#define GNU_SOURCE_
#include <string.h>
#include <stdio.h>

#include "exit_code.h"
#include "import_data.h"
#include "bin_search_tree.h"
#include "avl_tree.h"
#include "compare_func.h"

#include "hash_table_open.h"
#include "hash_table_close.h"
#include <math.h>

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

// Подсчёт строк в файле
size_t count_lines_in_file(FILE *f)
{
    size_t count = 0;
    char buffer[TEMP_STR_LEN];
    while (fgets(buffer, sizeof(buffer), f))
        count++;
    rewind(f);
    return count;
}

hash_table_open *file_to_hash_table_open(FILE *f)
{
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_open *table = hash_table_open_create((int)ceil(word_count * OPEN_HASH_TABLE_K));

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        rc = hash_table_open_add(&table, str);
        if (rc != OK)
        {
            hash_table_open_destroy(table);
            return NULL;
        }
        s = getline(&str, &len, f);
    }

    return table;
}

hash_table_close *file_to_hash_table_close(FILE *f)
{
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_close *table = hash_table_close_create((int)ceil(word_count * CLOSE_HASH_TABLE_K));

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        rc = hash_table_close_add(&table, str);
        if (rc != OK)
        {
            hash_table_close_destroy(table);
            return NULL;
        }
        s = getline(&str, &len, f);
    }

    return table;
}
