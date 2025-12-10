#ifndef HASH_CLOSE_TABLE_H__
#define HASH_CLOSE_TABLE_H__

#include "common_define.h"
#include "list.h"
#include "hash_type.h"
#include "compare_func.h"

typedef struct hash_table_close hash_table_close;

hash_table_close *hash_table_close_create(size_t len);
void hash_table_close_destroy(hash_table_close *hash_table);

int hash_table_close_add(hash_table_close **hash_table_ptr, char *value);

int hash_table_close_del(hash_table_close *hash_table, char *value);

bool hash_table_close_contain(hash_table_close *hash_table, char *value);

void hash_table_close_print(hash_table_close *hash_table);

int hash_table_close_restructuring(hash_table_close **table_ptr);

int list_add_to_hash_table_close(node_t *node, void *table_ptr);

double hash_table_close_load_factor(hash_table_close *table);
int hash_table_close_cmp_count(hash_table_close *hash_table, char *value);
double hash_table_close_avg_cmp_signle_run(hash_table_close *hash_table);
double hash_table_close_avg_cmp(hash_table_close *hash_table, int runs);

#endif
