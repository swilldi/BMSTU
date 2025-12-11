#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"
#include "hash_table_open.h"
#include <stdio.h>
#include "exit_code.h"
#include "math_func.h"


struct hash_table_open
{
    node_t **arr;
    size_t len;

    int cmp_count; 
};

hash_table_open *hash_table_open_create(size_t len)
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
            hash_table->cmp_count = 0;
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

static int hash_table_open_add_raw(hash_table_open *hash_table, char *value)
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

    int len = (int)len_list(hash_table->arr[index]);
    if (len > hash_table->cmp_count)
        hash_table->cmp_count = len;


    return OK;
}

int hash_table_open_add(hash_table_open **hash_table_ptr, char *value)
{
    hash_table_open *hash_table = *hash_table_ptr;

    int rc = hash_table_open_add_raw(hash_table, value);
    if (rc != OK)
        return rc;

    if (hash_table->cmp_count > MAX_CMP_COUNT)
    {
        rc = hash_table_open_restructuring(hash_table_ptr);
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
    hash_table->cmp_count = (int)len_list(hash_table->arr[index]) > hash_table->cmp_count ? (int)len_list(hash_table->arr[index]) : hash_table->cmp_count;
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

// Подсчет количества сравнений при поиске одного элемента
int hash_table_open_cmp_count(hash_table_open *hash_table, char *value)
{
    if (!hash_table || !value)
        return 0;

    hash_t index = get_str_hash(value) % hash_table->len;
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
double hash_table_open_avg_cmp(hash_table_open *hash_table, int runs)
{
    if (!hash_table || runs <= 0)
        return 0.0;

    double sum = 0.0;

    for (int i = 0; i < runs; i++)
        sum += hash_table_open_avg_cmp_single_run(hash_table);

    return sum / runs;
}

// TODO реструктуризация таблицы
int hash_table_open_restructuring(hash_table_open **table_ptr)
{
    int new_len = get_min_prime_num((*table_ptr)->len);
    
    hash_table_open *table = hash_table_open_create(new_len);
    if (!table)
        return MEMORY_ERROR;

    for (size_t i = 0; i < (*table_ptr)->len; i++)
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
    return hash_table_open_add_raw(table, list_data(node));
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




static int hash_table_open_add_raw_simple(hash_table_open *hash_table, char *value)
{
    hash_t index = get_str_hash_simple(value) % hash_table->len;
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
    if (len > hash_table->cmp_count)
        hash_table->cmp_count = len;


    return OK;
}

int hash_table_open_add_simple(hash_table_open **hash_table_ptr, char *value)
{
    hash_table_open *hash_table = *hash_table_ptr;

    int rc = hash_table_open_add_raw_simple(hash_table, value);
    if (rc != OK)
        return rc;

    if (hash_table->cmp_count > MAX_CMP_COUNT)
    {
        rc = hash_table_open_restructuring(hash_table_ptr);
        if (rc != OK)
            return rc;
    }

    return OK;
}

bool hash_table_open_contain_simple(hash_table_open *hash_table, char *value)
{
    hash_t index = get_str_hash_simple(value) % hash_table->len;
    node_t *cell = hash_table->arr[index];

    return list_contain(cell, value);
}
