#define GNU_SOURCE_
#include <string.h>
#include <stdio.h>

#include "bin_search_tree.h"
#include "avl_tree.h"
#include "hash_table_open.h"
#include "hash_table_close.h"
#include "compare_func.h"

// TODO сделать чтение универсальным
tree_node *file_to_tree(FILE *f);
avl_tree_node *file_to_avl_tree(FILE *f);
size_t count_lines_in_file(FILE *f);
hash_table_open *file_to_hash_table_open(FILE *f);
hash_table_close *file_to_hash_table_close(FILE *f);
