#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"
#include "hash_table_open.h"
#include <stdio.h>
#include <stdlib.h>
#include "exit_code.h"
#include "math_func.h"

#define MAX_RESTRUCT_ATTEMPTS 32

struct hash_table_open
{
    node_t **arr;
    size_t len;
    hash_func_ptr hash;

    int max_chain_len; 
};

hash_table_open *hash_table_open_create(size_t len, hash_func_ptr hash)
{
    if (!is_prime_num(len))
        len = get_min_prime_num(len);
    
    hash_table_open *hash_table = malloc(sizeof(hash_table_open));
    if (hash_table)
    {
        hash_table->arr = calloc(len, sizeof(node_t *));
        if (hash_table->arr)
        {
            hash_table->len = len;
            hash_table->max_chain_len = 0;
            hash_table->hash = hash;
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
    if (!hash_table)
        return;

    for (size_t i = 0; i < hash_table->len; i++)
        list_destroy(hash_table->arr[i]);
    
    free(hash_table->arr);
    free(hash_table);
}

static int hash_table_open_calc_max_chain_len(hash_table_open *hash_table)
{
    if (!hash_table || hash_table->len == 0)
        return 0;

    int max_len = 0;
    for (size_t i = 0; i < hash_table->len; i++)
    {
        int cur_len = (int)len_list(hash_table->arr[i]);
        if (cur_len > max_len)
            max_len = cur_len;
    }

    return max_len;
}

int hash_table_open_add_raw(hash_table_open *hash_table, char *value)
{
    hash_t index = hash_table->hash(value) % hash_table->len;
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

    int len = (int)len_list(hash_table->arr[index]);
    if (len > hash_table->max_chain_len)
        hash_table->max_chain_len = len;


    return OK;
}

int hash_table_open_add(hash_table_open **hash_table_ptr, char *value)
{
    hash_table_open *hash_table = *hash_table_ptr;

    int rc = hash_table_open_add_raw(hash_table, value);
    if (rc != OK)
        return rc;

    int attempts = 0;
    while (hash_table->max_chain_len > MAX_CMP_COUNT && attempts < MAX_RESTRUCT_ATTEMPTS)
    {
        rc = hash_table_open_restructuring(hash_table_ptr);
        if (rc != OK)
            return rc;

        hash_table = *hash_table_ptr;
        attempts++;
    }

    return OK;
}

int hash_table_open_del(hash_table_open *hash_table, char *value)
{
    hash_t index = hash_table->hash(value) % hash_table->len;
    node_t *cell = hash_table->arr[index];

    if (!list_contain(cell, value))
        return VALUE_NOT_EXITS;

    hash_table->arr[index] = list_del_by_valuet(cell, value, cmp_str);
    hash_table->max_chain_len = hash_table_open_calc_max_chain_len(hash_table);
    return OK;
}

bool hash_table_open_contain(hash_table_open *hash_table, char *value)
{
    hash_t index = hash_table->hash(value) % hash_table->len;
    node_t *cell = hash_table->arr[index];

    return list_contain(cell, value);
}

void hash_table_open_print(hash_table_open *hash_table)
{
    for (size_t i = 0; i < hash_table->len; i++)
    {
        printf("[%lu]: ", i);
        if (hash_table->arr[i])
            list_print(hash_table->arr[i], hash_table->hash);
        else
            printf("\n");
    }
}

// Подсчет количества сравнений при поиске одного элемента
int hash_table_open_cmp_count(hash_table_open *hash_table, char *value)
{
    if (!hash_table || !value)
        return 0;

    hash_t index = hash_table->hash(value) % hash_table->len;
    node_t *cur = hash_table->arr[index];
    int cmp_count = 0;

    while (cur)
    {
        cmp_count++;
        if (cmp_str(list_data(cur), value) == 0)
            break;

        cur = list_next(cur);
    }

    return cmp_count;
}

// Подсчет среднего количества сравнений для всех элементов таблицы (один прогон)
double hash_table_open_avg_cmp_single_run(hash_table_open *hash_table)
{
    if (!hash_table || hash_table->len == 0)
        return 0.0;

    long long total_cmp = 0;
    int elem_count = 0;

    for (size_t i = 0; i < hash_table->len; i++)
    {
        node_t *cur = hash_table->arr[i];
        while (cur)
        {
            total_cmp += hash_table_open_cmp_count(hash_table, (char *)list_data(cur));
            elem_count++;
            cur = list_next(cur);
        }
    }

    if (elem_count == 0)
        return 0.0;

    return (double)total_cmp / elem_count;
}

// Усреднение по нескольким прогонам
double hash_table_open_avg_cmp(hash_table_open *hash_table)
{
    if (!hash_table || TEST_COUNT_FOR_AVG_CMP <= 0)
        return 0.0;

    double sum = 0.0;

    for (int i = 0; i < TEST_COUNT_FOR_AVG_CMP; i++)
        sum += hash_table_open_avg_cmp_single_run(hash_table);

    return sum / TEST_COUNT_FOR_AVG_CMP;
}


static int list_add_to_hash_table_open(node_t *node, void *table_ptr)
{
    hash_table_open *table = *(hash_table_open **)table_ptr;
    return hash_table_open_add_raw(table, list_data(node));
}

// TODO реструктуризация таблицы
int hash_table_open_restructuring(hash_table_open **table_ptr)
{
    hash_table_open *old_table = *table_ptr;
    int new_len = get_min_prime_num((int)ceil(old_table->len * EXTAND_K));

    hash_table_open *table = hash_table_open_create(new_len, old_table->hash);
    if (!table)
        return MEMORY_ERROR;

    int rc = OK;

    for (size_t i = 0; i < old_table->len; i++)
    {
        if (old_table->arr[i])
        {
            rc = list_apply(old_table->arr[i], list_add_to_hash_table_open, &table);
            if (rc != OK)
            {
                hash_table_open_destroy(table);
                return rc;
            }
        }
    }

    table->max_chain_len = hash_table_open_calc_max_chain_len(table);

    hash_table_open_destroy(old_table);
    *table_ptr = table;
    
    return OK;
}



size_t hash_table_open_size(hash_table_open *hash_table)
{
    if (!hash_table || hash_table->len == 0)
        return 0;

    size_t elem_count = 0;

    for (size_t i = 0; i < hash_table->len; i++)
    {
        node_t *cur = hash_table->arr[i];
        while (cur)
        {
            elem_count++;
            cur = list_next(cur);
        }
    }

    return elem_count;
}

size_t hash_table_open_capacity(hash_table_open *hash_table)
{
    return hash_table ? hash_table->len : 0;
}
