#ifndef ARRAY_T_H__
#define ARRAY_T_H__

#include <stdio.h>
typedef struct
{
    char **data;
    size_t len;
    size_t max_len;
} array_t;

#endif
