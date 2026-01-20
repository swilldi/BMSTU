#ifndef MATRIX_OPERATIONS_H__
#define MATRIX_OPERATIONS_H__

#include <stdlib.h>
#include "io_funcs.h"

int check_row(int *row, size_t len, short digit);

void copy_array(int *arr_1, int *arr_2, size_t len);

void set_row(int *arr, size_t col);

size_t action(int (*matrix)[MAX_COLUNMS], size_t rows, size_t columns, short digit);

#endif
