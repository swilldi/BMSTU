#ifndef ARR_H__
#define ARR_H__

#include <stdbool.h>

typedef enum
{
    OK = 0,
    ARR_SMALL_SIZE_ERR,
} error;

bool is_prime_num(int num);
int next_prime_num(int num);
void arr_fill_prime_num(int *arr, int n);
int arr_add_after_even(int *src, int src_n, int *dst, int *dst_n, int fill_num);

#endif
