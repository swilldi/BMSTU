#ifndef HASH_TYPE_H__
#define HASH_TYPE_H__

#include <stdlib.h>

#define HASH_BASE 31
typedef unsigned long long hash_t;
typedef  hash_t (*hash_func_ptr)(char*);

hash_t get_str_hash(char *str);
hash_t get_str_hash_simple(char *str);

#endif
