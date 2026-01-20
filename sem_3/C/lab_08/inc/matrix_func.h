#ifndef MATRIX_FUNC_H__
#define MATRIX_FUNC_H__

#include "exit_code.h"
#include "stdlib.h"

typedef double **matrix_t;
typedef double *row_col_t;
#define EPS 1e-5

error solve_slae_gauss(double **a, double *f, double *x, int n);
void set_matrix_col(matrix_t mtr, row_col_t col, size_t n, size_t i_col);
error inverse_matrix(matrix_t *inv_mtr, matrix_t source_mtr, size_t n);
error mult_matrix(matrix_t *res, matrix_t mtr_a, matrix_t mtr_b, size_t n, size_t m, size_t k);
error sum_matrix(matrix_t *res, matrix_t mtr_a, matrix_t mtr_b, size_t n, size_t m);

#endif
