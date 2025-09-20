#ifndef LARGE_NUM_STUCT_H__
#define LARGE_NUM_STUCT_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define DIGITS_COUNT_MAX 40
#define EXPONENTA_COUNT_MAX 5
#define STR_INPUT_LEN  (1 + DIGITS_COUNT_MAX + 3 + EXPONENTA_COUNT_MAX)

#define MAX_EXP 99999
#define MIN_EXP -99999

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

