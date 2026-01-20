#ifndef DYNAMIC_MATRIX_H__
#define DYNAMIC_MATRIX_H__

#include "matrix_func.h"
#include "stdlib.h"

matrix_t create_matrix(size_t n, size_t m);
void free_matrix(matrix_t mtr);

#endif
