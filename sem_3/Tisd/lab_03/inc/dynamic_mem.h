#ifndef DYNAMIC_MEM_H__
#define DYNAMIC_MEM_H__

#include "stdlib.h"
#include "matrix_struct.h"

#define START_NUMBER_VALUES 50

int create_matrix_razr(matrix_t *mtr, size_m n, size_m m, type_matrixt type);
int extract_matrix_values(matrix_t *matrix);
void get_dim_data(dim_data_t *data, matrix_t *mtr, size_t ind);
void free_dim_data(dim_data_t *data);

int** create_matrix(size_t n, size_t m);
void free_matrix(matrix_data_t *matrix, size_t n);
int create_dim_data(dim_data_t *data, size_t len);
void free_matrix_razr(matrix_t *m);
void free_dim_data(dim_data_t *data);

#endif
