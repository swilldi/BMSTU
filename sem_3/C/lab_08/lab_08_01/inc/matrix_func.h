#ifndef MATRIX_FUNC_H__
#define MATRIX_FUNC_H__

#include "matrix_t.h"
#include "stdlib.h"

matrix_t matrix_to_sqr(matrix_t matrix);
matrix_t expand_matrix(matrix_t, size_t new_n);

matrix_t transpose_matrix(matrix_t origin, size_t n, size_t m);
int mult_row_by_col(int *row, int *col, size_t n);
matrix_t mult_sqr_matrix(matrix_t a, matrix_t b, size_t n);
matrix_t power_sqr_matrix(matrix_t a, size_t n, size_t degree);

#endif
