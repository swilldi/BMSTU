#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "exit_code.h"
#include "import_data.h"
#include "bin_search_tree.h"
#include "avl_tree.h"
#include "compare_func.h"

#include "hash_table_open.h"
#include "hash_table_close.h"
#include <math.h>

// TODO сделать чтение универсальным
bin_tree_node *file_to_bin_tree(FILE *f)
{
    rewind(f);
    bin_tree_node *tree = bin_tree_create();

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        tree = bin_tree_insert(tree, bin_tree_node_create(str), cmp_str);
        s = getline(&str, &len, f);
    }
    free(str);

    return tree;
}

// TODO сделать чтение универсальным
avl_tree_node *file_to_avl_tree(FILE *f)
{
    rewind(f);
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
    free(str);
    
    return tree;
}

// Подсчёт строк в файле
size_t count_lines_in_file(FILE *f)
{
    rewind(f);
    size_t count = 0;
    char buffer[TEMP_STR_LEN];
    while (fgets(buffer, sizeof(buffer), f))
        count++;
    rewind(f);
    return count;
}

bool file_is_empty(FILE *f)
{
    fseek(f, 0, SEEK_END);
    size_t end = ftell(f);
    rewind(f);
    return end == 0;
}

hash_table_open *file_to_hash_table_open(FILE *f, hash_func_ptr hash)
{
    rewind(f);
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_open *table = hash_table_open_create((int)ceil(word_count * OPEN_HASH_TABLE_K), hash);

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

hash_table_close *file_to_hash_table_close(FILE *f, hash_func_ptr hash)
{
    rewind(f);
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_close *table = hash_table_close_create((int)ceil(word_count * CLOSE_HASH_TABLE_K), hash);

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






hash_table_open *file_to_hash_table_open_no_rest(FILE *f, hash_func_ptr hash)
{
    rewind(f);
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_open *table = hash_table_open_create((int)ceil(word_count * OPEN_HASH_TABLE_K), hash);

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        rc = hash_table_open_add_raw(table, str);
        if (rc != OK)
        {
            hash_table_open_destroy(table);
            return NULL;
        }
        s = getline(&str, &len, f);
    }

    return table;
}

hash_table_close *file_to_hash_table_close_no_rest(FILE *f, hash_func_ptr hash)
{
    rewind(f);
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_close *table = hash_table_close_create((int)ceil(word_count * CLOSE_HASH_TABLE_K), hash);

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        rc = hash_table_close_add_raw(table, str);
        if (rc != OK)
        {
            hash_table_close_destroy(table);
            return NULL;
        }
        s = getline(&str, &len, f);
    }

    return table;
}

hash_table_open *file_to_hash_table_open_test(FILE *f, hash_func_ptr hash)
{
    rewind(f);
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_open *table = hash_table_open_create((int)ceil(word_count * OPEN_HASH_TABLE_K), hash);

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        rc = hash_table_open_add_test(&table, str);
        if (rc != OK)
        {
            hash_table_open_destroy(table);
            return NULL;
        }
        s = getline(&str, &len, f);
    }

    return table;
}

hash_table_close *file_to_hash_table_close_test(FILE *f, hash_func_ptr hash)
{
    rewind(f);
    int rc;
    size_t word_count = count_lines_in_file(f);
    hash_table_close *table = hash_table_close_create((int)ceil(word_count * CLOSE_HASH_TABLE_K), hash);

    char *str = NULL;
    size_t len = 0;
    ssize_t s = getline(&str, &len, f);
    while (s != -1)
    {
        char *end_str = strchr(str, '\n');
        if (end_str)
            *end_str = '\0';
        
        // printf("len: %ld | %s\n", s, str);
        rc = hash_table_close_add_test(&table, str);
        if (rc != OK)
        {
            hash_table_close_destroy(table);
            return NULL;
        }
        s = getline(&str, &len, f);
    }

    return table;
}
