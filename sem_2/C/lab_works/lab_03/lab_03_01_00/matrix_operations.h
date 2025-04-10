#ifndef MATRIX_OPERATIONS
#define MATRIX_OPERATIONS

#include <stdlib.h>
#include "array_funcs.h"

int check_row(int *row, size_t len, short digit);

void copy_array(int *arr_1, int *arr_2, size_t len);

void set_special_row(int *arr, size_t col);

void action(int (*matrix)[MAX_COLUNMS], size_t rows, size_t colunms, int *arr);

#endif
