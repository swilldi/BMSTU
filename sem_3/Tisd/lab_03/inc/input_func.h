#ifndef INPUT_FUNC_H__
#define INPUT_FUNC_H__


#include "exit_code.h"
#include "matrix_struct.h"
#include "dynamic_mem.h"
#include "stdio.h"

#define BUFF_LEN 256
#define PATH_LEN 250

typedef int (*method_input_matrix)(matrix_data_t matrix, size_m n, size_m m, FILE *f);

int input_size(size_m *num, FILE *f);
int input_num(int *num, FILE *f);
int input_str(char *str, size_t max_len, FILE *f);
int input_matrix(matrix_data_t *matrix, size_m *n, size_m *m, FILE *f, method_input_matrix input_func);
int input_matrix_sizes(size_m *n, size_m *m, FILE *f);
int input_matrix_classic(matrix_data_t matrix, size_m n, size_m m, FILE *f);
int input_matrix_coord(matrix_data_t matrix, size_m n, size_m m, FILE *f);
int input_command(int *cmd, command_t type);

#endif
