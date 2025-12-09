#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"
#include "hash_table_open.h"
#include <stdio.h>
#include "exit_code.h"

#define MAX_LOAD_FACTOR 0.7
#define MAX_CMP_COUNT 3

struct hash_table_open
{
    node_t **arr;
    size_t len;

    int elem_count;
    int cmp_count; 
};


#include <math.h>
bool is_prime_num(int num)
{
    for (int i = 2; i < sqrt(num) + 1; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int get_min_prime_num(int num)
{
    num += 1;
    while (!is_prime_num(num))
        num += 1;

    return num;
}

hash_table_open *hash_table_open_create(size_t len)
{
    len = get_min_prime_num(len);
    
    hash_table_open *hash_table = malloc(sizeof(hash_table_open));
    if (hash_table)
    {
        hash_table->arr = malloc(len * list_node_size());
        if (hash_table->arr)
        {
            hash_table->len = len;
            hash_table->elem_count = 0;
            hash_table->cmp_count = 0;
            for (size_t i = 0; i < len; i++)
                hash_table->arr[i] = list_create();
        }
        else
        {
            free(hash_table);
            hash_table = NULL;
        }
    }

    return hash_table;
}

void hash_table_open_destroy(hash_table_open *hash_table)
{
    for (size_t i = 0; i < hash_table->len; i++)
        list_destroy(hash_table->arr[i]);
    
    free(hash_table);
}

int hash_table_open_add(hash_table_open *hash_table, char *value)
{
    hash_t index = get_str_hash(value) % hash_table->len;
    node_t *cell = hash_table->arr[index];

    if (list_contain(cell, value))
        return VALUE_EXITS;
    
    node_t *new_node = list_create_node(value);
    if (!new_node)
    {
        // TODO почистить память
        return MEMORY_ERROR;
    }

    
    hash_table->arr[index] = list_add_end(cell, new_node);

    hash_table->cmp_count = (int)len_list(cell) > hash_table->cmp_count ? len_list(cell) : hash_table->cmp_count;
    hash_table->elem_count += 1;

    // TODO обработка ошибки
    // printf("%lf\n", hash_table_open_load_factor(hash_table));
    int rc;
    if (hash_table_open_load_factor(hash_table) > MAX_LOAD_FACTOR || hash_table->cmp_count > MAX_CMP_COUNT)
    {
        rc = hash_table_open_restructuring(&hash_table);
        if (rc != OK)
            return rc;
    }

    return OK;
}

int hash_table_open_del(hash_table_open *hash_table, char *value)
{
    hash_t index = get_str_hash(value) % hash_table->len;
    node_t *cell = hash_table->arr[index];

    if (!list_contain(cell, value))
        return VALUE_NOT_EXITS;

    hash_table->arr[index] = list_del_by_valuet(cell, value, cmp_str);
    hash_table->elem_count -= 1;
    return OK;
}

bool hash_table_open_contain(hash_table_open *hash_table, char *value)
{
    hash_t index = get_str_hash(value) % hash_table->len;
    node_t *cell = hash_table->arr[index];

    return list_contain(cell, value);
}

void hash_table_open_print(hash_table_open *hash_table)
{
    for (size_t i = 0; i < hash_table->len; i++)
    {
        printf("[%lu]: ", i);
        if (hash_table->arr[i])
            list_print(hash_table->arr[i]);
        else
            printf("\n");
    }
}

// TODO реструктуризация таблицы
int hash_table_open_restructuring(hash_table_open **table_ptr)
{
    int new_len = get_min_prime_num((*table_ptr)->len);
    
    hash_table_open *table = hash_table_open_create(new_len);

    for (size_t i = 0; i < table->len; i++)
    {
        // TODO обработка ошибок
        if ((*table_ptr)->arr[i])
            list_apply((*table_ptr)->arr[i], list_add_to_hash_table_open, table);
    }

    hash_table_open_destroy(*table_ptr);
    *table_ptr = table;
    
    return OK;
}

int list_add_to_hash_table_open(node_t *node, void *table_ptr)
{
    hash_table_open *table = table_ptr;
    if (!hash_table_open_add(table, list_data(node)))
        return MEMORY_ERROR;
    else
        return OK;
}

double hash_table_open_load_factor(hash_table_open *table)
{
    return (double)table->elem_count / table->len;
}
