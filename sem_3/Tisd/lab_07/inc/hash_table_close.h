#ifndef HASH_CLOSE_TABLE_H__
#define HASH_CLOSE_TABLE_H__

#include <stdio.h>
#include <stdbool.h>
#include "common_define.h"
#include "hash_type.h"
#include "compare_func.h"
#include "exit_code.h"
#include "math_func.h"

typedef struct hash_table_close hash_table_close;

hash_table_close *hash_table_close_create(size_t len, hash_func_ptr hash);
void hash_table_close_destroy(hash_table_close *hash_table);
int hash_table_close_add(hash_table_close **hash_table_ptr, char *value);
// TODO Изменить удаление
int hash_table_close_del(hash_table_close *hash_table, char *value);
// TODO Изменить поиск
bool hash_table_close_contain(hash_table_close *hash_table, char *value);
// Подсчет количества сравнений при поиске одного элемента
int hash_table_close_cmp_count(hash_table_close *hash_table, char *value);
// Подсчет среднего количества сравнений для всех элементов таблицы (один прогон);
double hash_table_close_avg_cmp_signle_run(hash_table_close *hash_table);
// Усреднение по нескольким прогонам
double hash_table_close_avg_cmp(hash_table_close *hash_tableh);
void hash_table_close_print(hash_table_close *hash_table);
int hash_table_close_restructuring(hash_table_close **table_ptr);
double hash_table_close_load_factor(hash_table_close *table);
size_t hash_table_close_size(hash_table_close *hash_table);
size_t hash_table_close_capacity(hash_table_close *hash_table);
size_t hash_table_close_cell_size(void);
int hash_table_close_add_raw(hash_table_close *hash_table, char *value);
int hash_table_close_add_test(hash_table_close **hash_table_ptr, char *value);


#endif
