#ifndef TEST_H__
#define TEST_H__

#include <time.h>
#include <stdio.h>
#include "exit_code.h"



#include "test.h"
#include "input_func.h"
#include "output_func.h"
#include "dynamic_mem.h"
#include "matrix_struct.h"
#include "exit_code.h"
#include "matrix_func.h"
#include "enums.h"


#define ST_HEADER_METHOD "| count | by_table, сек | by_key, сек | by_key / by_table, %% | cars mem, b  | keys mem, b | keys / cars, %% |\n"
#define ST_HEADER_SORT   "| count |  quick, сек   | shaker, сек |   quick / shaker, %%  | cars mem, b  | keys mem, b | keys / cars, %% |\n"
#define ST_SEPARATOR     "--------+---------------+-------------+----------------------+--------------+-------------+-----------------\n"

void test_csr(FILE *f, double *res_time, size_t *res_memory);
void test_classic(FILE *f, double *res_time, size_t *res_memory);
int test_mult_method(void);
void get_k_razr(FILE *f, double *k_razr);
void get_sizes(FILE *f, size_m *n, size_m *m);


#endif
