#include "input_func.h"
#include "dynamic_mem.h"
#include "matrix_struct.h"
#include "exit_code.h"
#include "matrix_func.h"
#include "enums.h"
#include "time.h"

#define TEST_COUNT 10
#define PRE_TEST_COUNT 10


int test_compress(char *file_name, double *time_res, size_t *memory_res);
int test_classic(char *file_name, size_t *time_res, size_t *memory_res);
int start_testa(void);
size_t amount_no_zero(matrix_data_t mtr, size_t n, size_t m);
int get_matrix_info(char *file_name, double *k_razr_1, size_t *max_elem_1, double *k_razr_2, size_t *max_elem_2);

