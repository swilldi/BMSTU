#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdlib.h>

typedef unsigned int** matrix_t;
matrix_t matrix_create(int n, int m);
void matrix_destoy(matrix_t matrix, int n);
void matrix_print(matrix_t matrix, int n);

#endif
