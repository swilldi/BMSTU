#ifndef DYNAMIC_MEM_H__
#define DYNAMIC_MEM_H__

#include "stdlib.h"
#include "matrix_struct.h"

int** create_matrix(size_t n, size_t m);
void free_matrix(matrix_data_t matrix, size_t n);
int create_dim_data(dim_data_t *data, size_t len);

#endif
