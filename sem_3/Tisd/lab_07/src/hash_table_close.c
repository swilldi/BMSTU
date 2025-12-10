#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"
#include "hash_table_close.h"
#include <stdio.h>
#include "exit_code.h"
#include "math_func.h"
#include <string.h>

#define MAX_LOAD_FACTOR 0.7

typedef enum
{
    EMPTY,
    DELETED,
    SETED
} cell_status;

typedef struct 
{
    char value[STR_LEN];
    cell_status status;
} table_cell; 

struct hash_table_close
{
    table_cell *arr;
    size_t len;
    int elem_count;
};

hash_table_close *hash_table_close_create(size_t len)
{
    if (!is_prime_num(len))
        len = get_min_prime_num(len);
    
    hash_table_close *hash_table = malloc(sizeof(hash_table_close));
    if (hash_table)
    {
        hash_table->arr = malloc(len * sizeof(table_cell));
        if (hash_table->arr)
        {
            hash_table->len = len;
            for (size_t i = 0; i < len; i++)
                hash_table->arr[i].status = EMPTY;
            hash_table->elem_count = 0;
        }
        else
        {
            free(hash_table);
            hash_table = NULL;
        }
    }

    return hash_table;
}

void hash_table_close_destroy(hash_table_close *hash_table)
{
    if (!hash_table)
        return;
    
    free(hash_table->arr);
    free(hash_table);
}

// TODO Изменить добавление без реструктуризации
static int hash_table_close_add_raw(hash_table_close *hash_table, char *value)
{
    hash_t start_index = get_str_hash(value) % hash_table->len;

    for (size_t step = 0; step < hash_table->len; step++)
    {
        size_t index = (start_index + step) % hash_table->len;
        table_cell *cell = &hash_table->arr[index];

        if (cell->status == SETED)
        {
            // занято — продолжаем пробирование
            continue;
        }

        // EMPTY или DELETED — трактуем как свободные при вставке
        strcpy(cell->value, value);
        cell->status = SETED;
        hash_table->elem_count += 1;
        return OK;
    }

    // Таблица полностью занята (все SETED) — в нормальной работе
    // сюда доходить не должны, так как реструктуризацию делаем заранее.
    return MEMORY_ERROR;
}

int hash_table_close_add(hash_table_close **hash_table_ptr, char *value)
{
    hash_table_close *hash_table = *hash_table_ptr;

    int rc = hash_table_close_add_raw(hash_table, value);
    if (rc != OK)
        return rc;

    if (hash_table_close_load_factor(hash_table) > MAX_LOAD_FACTOR)
    {
        rc = hash_table_close_restructuring(hash_table_ptr);
        if (rc != OK)
            return rc;
    }

    return OK;
}

// TODO Изменить удаление
int hash_table_close_del(hash_table_close *hash_table, char *value)
{
    hash_t start_index = get_str_hash(value) % hash_table->len;

    for (size_t step = 0; step < hash_table->len; step++)
    {
        size_t index = (start_index + step) % hash_table->len;
        table_cell *cell = &hash_table->arr[index];

        if (cell->status == EMPTY)
        {
            // Пустая ячейка разрывает цепочку — дальше элемента точно нет
            return VALUE_NOT_EXITS;
        }

        if (cell->status == SETED && strcmp(cell->value, value) == 0)
        {
            cell->status = DELETED;
            hash_table->elem_count -= 1;
            return OK;
        }

        // DELETED или SETED с другим значением — продолжаем пробирование
    }

    return VALUE_NOT_EXITS;
}

// TODO Изменить поиск
bool hash_table_close_contain(hash_table_close *hash_table, char *value)
{
    hash_t start_index = get_str_hash(value) % hash_table->len;

    for (size_t step = 0; step < hash_table->len; step++)
    {
        size_t index = (start_index + step) % hash_table->len;
        table_cell *cell = &hash_table->arr[index];

        if (cell->status == EMPTY)
        {
            // Пустая ячейка разрывает цепочку — элемента нет
            return false;
        }

        if (cell->status == SETED && strcmp(cell->value, value) == 0)
        {
            return true;
        }

        // DELETED или SETED с другим значением — продолжаем поиск
    }

    return false;
}

// Подсчет количества сравнений при поиске одного элемента
int hash_table_close_cmp_count(hash_table_close *hash_table, char *value)
{
    if (!hash_table || !value)
        return 0;

    hash_t start_index = get_str_hash(value) % hash_table->len;
    int cmp_count = 0;

    for (size_t step = 0; step < hash_table->len; step++)
    {
        size_t index = (start_index + step) % hash_table->len;
        table_cell *cell = &hash_table->arr[index];

        if (cell->status == EMPTY)
        {
            // Пустая ячейка разрывает цепочку — элемента нет
            break;
        }

        if (cell->status == SETED)
        {
            cmp_count++;
            if (strcmp(cell->value, value) == 0)
                break;
        }

        // DELETED или SETED с другим значением — продолжаем пробирование
    }

    return cmp_count;
}

// Подсчет среднего количества сравнений для всех элементов таблицы (один прогон)
double hash_table_close_avg_cmp_signle_run(hash_table_close *hash_table)
{
    if (!hash_table || hash_table->elem_count == 0)
        return 0.0;

    long long total_cmp = 0;
    int elem_count = 0;

    for (size_t i = 0; i < hash_table->len; i++)
    {
        table_cell *cell = &hash_table->arr[i];
        if (cell->status == SETED)
        {
            total_cmp += hash_table_close_cmp_count(hash_table, cell->value);
            elem_count++;
        }
    }

    if (elem_count == 0)
        return 0.0;

    return (double)total_cmp / elem_count;
}

// Усреднение по нескольким прогонам
double hash_table_close_avg_cmp(hash_table_close *hash_table, int runs)
{
    if (!hash_table || runs <= 0)
        return 0.0;

    double sum = 0.0;

    for (int i = 0; i < runs; i++)
        sum += hash_table_close_avg_cmp_signle_run(hash_table);

    return sum / runs;
}

void hash_table_close_print(hash_table_close *hash_table)
{
    for (size_t i = 0; i < hash_table->len; i++)
    {
        table_cell cell = hash_table->arr[i];
        printf("[%lu]: ", i);
        if (cell.status == SETED)
            printf("%s (%lld | %lld)", cell.value, get_str_hash(cell.value), get_str_hash(cell.value) % hash_table->len);
        
        printf("\n");
    }
}

// Увеличиваем массив в 2 раза
int hash_table_close_restructuring(hash_table_close **table_ptr)
{
    int new_len = get_min_prime_num((*table_ptr)->len);
    
    hash_table_close *table = hash_table_close_create(new_len);
    if (!table)
        return MEMORY_ERROR;

    for (size_t i = 0; i < (*table_ptr)->len; i++)
    {
        // TODO обработка ошибок
        table_cell cell = (*table_ptr)->arr[i];
        if (cell.status == SETED)
            hash_table_close_add_raw(table, cell.value);
    }

    hash_table_close_destroy(*table_ptr);
    *table_ptr = table;
    
    return OK;
}

double hash_table_close_load_factor(hash_table_close *table)
{
    return (double)table->elem_count / table->len;
}
