#include "large_num_sturct.h"
#include <stdbool.h>
#include "io_func.h"

#include "stdio.h"

void get_partial_dividend(large_num_t *dividend, large_num_t *divider, large_num_t *partial_dividend) 
{
    // проверка будет ли неполное делимое, с длиной делителя, больше чем делитель
    bool dividend_is_greater = true;
    for (size_t i = 1; i <= divider->len; i++)
    {
        int dividend_v = dividend->mantissa[dividend->len - i], divider_v = divider->mantissa[divider->len - i];
        if (i > dividend->len)
        {
            if (divider_v != 0)
            {
                dividend_is_greater = false;
                break;
            }
        }
        else
        {
            if (dividend_v > divider_v)
                break;
            else if (dividend_v < divider_v)
            {
                dividend_is_greater = false;
                break;
            }
        }
    }

    // заполнение неполного делимого

    if (dividend->len >= divider->len + !dividend_is_greater)
    {
        partial_dividend->len = divider->len + !dividend_is_greater;
    }
    else
    {
        size_t diff = divider->len - dividend->len + !dividend_is_greater;
        dividend->exponent -= diff;
        partial_dividend->exponent += diff;

        partial_dividend->len = dividend->len;
    }

    for (size_t i = 1; i <= partial_dividend->len; i++)
    {
        partial_dividend->mantissa[partial_dividend->len - i] = dividend->mantissa[dividend->len - i];
    }
}

int get_t(large_num_t *part_dividend, large_num_t *divider)
{
    int a, b;
    
    if (part_dividend->len > divider->len)
        a = 10 * part_dividend->mantissa[1] + part_dividend->mantissa[0];
    else
        a = part_dividend->mantissa[0];
    b = divider->mantissa[0];

    return a / b;
}


void large_num_multiply_digit(large_num_t *multiplicand, int multiplier, large_num_t *res);

void large_num_add(large_num_t *augend, large_num_t *addend, large_num_t *res);

// void update_partial_dividend(large_num_t part_dividend, la)

// void large_num_divide(large_num_t *dividend, large_num_t *divider, large_num_t *res)
// {
//     large_num_t partial_dividend = { .len = 0, .sign = false, .exponent = 0};

//     get_partial_dividend(dividend, divider, &partial_dividend);
//     int t;
//     t = get_t(&partial_dividend, divider);

    
//     print_num(&partial_dividend);
//     res->len++;
// }


