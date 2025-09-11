#ifndef LARGE_NUM_STUCT_H__
#define LARGE_NUM_STUCT_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define DIGITS_COUNT_MAX 7

typedef struct
{
    uint8_t digits[DIGITS_COUNT_MAX + 1];
    size_t len;
} ulong_num_t;

typedef struct
{
    ulong_num_t mantissa;
    int exponent;
    bool sign;
} large_num_t;

#endif
