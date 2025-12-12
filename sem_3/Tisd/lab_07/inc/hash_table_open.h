#ifndef HASH_OPEN_TABLE_H__
#define HASH_OPEN_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"
#include "exit_code.h"
#include "math_func.h"

typedef struct hash_table_open hash_table_open;

#define MAX_RESTRUCT_ATTEMPTS 32

hash_table_open *hash_table_open_create(size_t len, hash_func_ptr hash);

void hash_table_open_destroy(hash_table_open *hash_table);
int hash_table_open_add(hash_table_open **hash_table_ptr, char *value);
int hash_table_open_del(hash_table_open *hash_table, char *value);
bool hash_table_open_contain(hash_table_open *hash_table, char *value);
void hash_table_open_print(hash_table_open *hash_table);
// Подсчет количества сравнений при поиске одного элемента
int hash_table_open_cmp_count(hash_table_open *hash_table, char *value);
// Подсчет среднего количества сравнений для всех элементов таблицы (один прогон)
double hash_table_open_avg_cmp_single_run(hash_table_open *hash_table);
// Усреднение по нескольким прогонам
double hash_table_open_avg_cmp(hash_table_open *hash_table);
// реструктуризация таблицы
int hash_table_open_restructuring(hash_table_open **table_ptr);
size_t hash_table_open_size(hash_table_open *hash_table);
size_t hash_table_open_capacity(hash_table_open *hash_table);
int hash_table_open_add_raw(hash_table_open *hash_table, char *value);


#endif
