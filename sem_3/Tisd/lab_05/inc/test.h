#ifndef TEST_H__
#define TEST_H__

#include <stdio.h>
#include <stdbool.h>

#include "exit_code.h"
#include "io_func.h"
#include "enums.h"
#include "queue_array_func.h"
#include "queue_list_func.h"


size_t count_lines_in_file(FILE *f);
q_type *read_data_from_file(const char *filename, size_t *count);
int test_queue_array(q_type *arr, size_t n, double *res_time);
int test_queue_list(q_type *arr, size_t n, double *res_time);
int run_compare_tests(void);

#endif
