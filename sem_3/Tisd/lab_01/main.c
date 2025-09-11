#include <stdio.h>
#include "math_func.h"
#include "large_num_struct.h"
#include "io_func.h"


int main(void)
{
    large_num_t a = { .exponent = 0, .sign = false, .mantissa = { .digits = {7, 6, 5, 4, 3, 2, 1}, .len = 7} };
    large_num_t b = { .exponent = 0, .sign = false, .mantissa = { .digits = {8, 4, 7, 3}, .len = 4} };
    large_num_t res;
    
    large_num_divide(&a, &b, &res);

    print_large_num_info(&res);
}

