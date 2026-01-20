#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#include "exit_code.h"
#include "input_func.h"
#include "stdio.h"
#include <stdbool.h>

error read_matrix(FILE *f, matrix_t mtr, size_t n, size_t m);
error read_matrix_sizes(FILE *f, size_t *n, size_t *m);
void write_matrix(FILE *f, matrix_t mtr, size_t n, size_t m);
error read_full_matrix(FILE *f, matrix_t *mtr, size_t *n, size_t *m);
error check_file(FILE *f);

#endif
