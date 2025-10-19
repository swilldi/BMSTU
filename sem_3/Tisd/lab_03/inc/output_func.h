#ifndef OUTPUT_FUNC_H__
#define OUTPUT_FUNC_H__

#include "matrix_struct.h"
#include <stdio.h>
#include <stdbool.h>

void print_matrix(matrix_data_t matrix, size_t n, size_t m);
void print_razr_debug(matrix_t *mtr);
void print_csr_matrix(matrix_t *mtr);
void print_csr_coord(matrix_t *mtr);
void print_input_cmd_list(void);
void print_output_cmd_list(void);
void print_err_msg(int code);

#endif 
