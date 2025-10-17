#ifndef MATRIX_FUNC_H__
#define MATRIX_FUNC_H__

#include "matrix_struct.h"
#include "exit_code.h"
#include <stdlib.h>



int matrix_to_csr(matrix_t *m_csr, matrix_data_t mtr, size_m n, size_m m);
int matrix_to_csc(matrix_t *m_csr, matrix_data_t mtr, size_m n, size_m m);
int mult_row_by_col(dim_data_t *d_csr, dim_data_t *d_csc);
int mult_csr_by_csc(matrix_t *mtr, matrix_t *m_csr, matrix_t *m_csc);

int classic_mult(matrix_data_t *res, matrix_data_t a, matrix_data_t b, size_t n, size_t m, size_t k);


#endif
