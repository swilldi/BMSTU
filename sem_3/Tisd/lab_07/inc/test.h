#ifndef TEST_H__
#define  TEST_H__

#include <stdio.h>
#include <string.h>


void get_file_info(char *filename, int *n, int *l, int *r);

int test_avg_cmp(void);
int test_avg_time_to_del(void);
int test_time_efficiency(void);
int test_hash_efficiency(void);

#endif
