#include <stdio.h>
#include "math_func.h"
#include "large_num_sturct.h"
#include "io_func.h"


int main(void)
{
    large_num_t dividend = { { 5, 2, 1 }, 0, 3, false},
                divider = { { 5 }, 0, 1, false},
                result;
    // large_num_divide(&dividend, &divider, &result);
    large_num_subtract(&dividend, &divider, &result);
    print_num(&result);
}

