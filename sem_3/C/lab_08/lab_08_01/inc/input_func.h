#ifndef INPUT_FUNC_HH_
#define INPUT_FUNC_HH_

#include <stdlib.h>
#include <matrix_t.h>

int input_ulong(size_t *num);
int input_int(int *num);
int input_matrix(matrix_t matrix, size_t n, size_t m);
int input_matrix_size(size_t *n, size_t *m);

#endif
