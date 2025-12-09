#ifndef HASH_OPEN_TABLE_H__
#define HASH_OPEN_TABLE_H__

#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"

typedef struct hash_table_open hash_table_open;

hash_table_open *hash_table_open_create(size_t len);
void hash_table_open_destroy(hash_table_open *hash_table);

int hash_table_open_add(hash_table_open *hash_table, char *value);

int hash_table_open_del(hash_table_open *hash_table, char *value);

bool hash_table_open_contain(hash_table_open *hash_table, char *value);

void hash_table_open_print(hash_table_open *hash_table);

int hash_table_open_restructuring(hash_table_open **table_ptr);

int list_add_to_hash_table_open(node_t *node, void *table_ptr);

double hash_table_open_load_factor(hash_table_open *table);

#endif
