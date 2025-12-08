#define GNU_SOURCE_
#include <string.h>
#include <stdio.h>

#include "bin_search_tree.h"
#include "compare_func.h"

// TODO сделать чтение универсальным
tree_node *file_to_tree(FILE *f);
