#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>

#include "bin_search_tree.h"
#include "avl_tree.h"
#include "hash_table_open.h"
#include "hash_table_close.h"
#include "compare_func.h"

// TODO сделать чтение универсальным
bin_tree_node *file_to_bin_tree(FILE *f);
avl_tree_node *file_to_avl_tree(FILE *f);
size_t count_lines_in_file(FILE *f);
hash_table_open *file_to_hash_table_open(FILE *f, hash_func_ptr hash);
hash_table_close *file_to_hash_table_close(FILE *f, hash_func_ptr hash);
hash_table_open *file_to_hash_table_open_no_rest(FILE *f, hash_func_ptr hash);
hash_table_close *file_to_hash_table_close_no_rest(FILE *f, hash_func_ptr hash);
bool file_is_empty(FILE *f);
hash_table_open *file_to_hash_table_open_test(FILE *f, hash_func_ptr hash);
hash_table_close *file_to_hash_table_close_test(FILE *f, hash_func_ptr hash);

