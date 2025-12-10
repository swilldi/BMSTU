#include <stdlib.h>

#include "hash_type.h"

hash_t get_str_hash(char *str)
{
    hash_t hash = 0;
    long long k = 1;

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        hash += (int)str[i] * k;
        k *= HASH_BASE;
     }

     return hash;
}
