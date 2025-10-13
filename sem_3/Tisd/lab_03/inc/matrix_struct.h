#ifndef MATRIX_STRUCT_H__
#define MATRIX_STRUCT_H__

#include <stdbool.h>
#include "enums.h"

#define size_m unsigned int

#define matrix_data_t int**

typedef struct
{
    type_matrixt type;

    size_m n;
    size_m m;

    unsigned int max_values;

    int *values;
    size_m *ind;
    size_m *dim;
} matrix_t;

typedef struct
{
    size_m *ind;
    int *value;

    size_m len;
} dim_data_t;

#endif 
