#ifndef OUTPUT_FUNC_H__
#define OUTPUT_FUNC_H__

#include "matrix_struct.h"
#include <stdio.h>
#include <stdbool.h>

void print_matrix(matrix_data_t matrix, size_t n, size_t m);
void print_csr_matrix(matrix_t *matrix);
size_t contain_num(int *pb, int *pe, int value);
void print_razr_debug(matrix_t *mtr);

#endif 
