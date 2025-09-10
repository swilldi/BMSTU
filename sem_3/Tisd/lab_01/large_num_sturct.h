#ifndef LARGE_NUM_STUCT_H__
#define LARGE_NUM_STUCT_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define DIGITS_COUNT_MAX 40

typedef struct
{
    uint8_t mantissa[DIGITS_COUNT_MAX + 1];
    int exponent;
    size_t len;
    bool sign;
} large_num_t;

#endif
