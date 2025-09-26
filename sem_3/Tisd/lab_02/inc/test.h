#ifndef TEST_H__
#define TEST_H__

#include <time.h>
#include "structs.h"
#include <stdio.h>
#include "file_func.h"
#include "exit_code.h"
#include "sort.h"
#include "table_func.h"

#define TEST_COUNT 5
#define PRE_TEST_COUNT 5

typedef int(*sort_type)(void*, size_t, size_t, comparator_t);
typedef int(*test_type)(FILE *, sort_type, double *);


int test(FILE *f, sort_type sort_method, double *res);
int test_by_key(FILE *f, sort_type sort_method, double *res);
int get_count(int num);
int test_table(sort_type sort);
int test_sort(test_type test_f);

#endif
