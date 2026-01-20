#include "arr.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define FIRST_PRIME_NUM 2

bool is_prime_num(int num)
{
    if (num < 2)
        return false;

    for (int i = 2; i < (int)(sqrt(num) + 1); i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int next_prime_num(int num)
{
    int next_prime = num + 1;
    while (!is_prime_num(next_prime))
        next_prime += 1;
    return next_prime;
}

void arr_fill_prime_num(int *arr, int n)
{
    int cur = FIRST_PRIME_NUM;
    for (int i = 0; i < n; i++)
    {
        arr[i] = cur;
        cur = next_prime_num(cur);
    }
}



int arr_add_after_even(int *src, int src_n, int *dst, int *dst_n, int fill_num)
{
    // подсчет количества четных элементов
    int n = 0;
    for (int i = 0; i < src_n; i++)
    {
        if (abs(src[i]) % 2 == 0)
            n += 1;
    }

    // проверка размера выходного массива
    if (src_n+ n > *dst_n)
    {
        *dst_n = src_n + n;
        return ARR_SMALL_SIZE_ERR;
    }

    // заполнение выходного массива
    int dst_shift = 0;
    for (int i = 0; i < src_n; i++)
    {
        dst[i + dst_shift] = src[i];
        if (abs(src[i]) % 2 == 0)
        {
            dst[i + dst_shift + 1] = fill_num;
            dst_shift += 1;
        }
    }
    return OK;
}
