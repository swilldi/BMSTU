#include <math.h>
#include <stdbool.h>
#include "math_func.h"

bool is_prime_num(int num)
{
    if (num < 2)
        return false;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int get_min_prime_num(int num)
{
    num += 1;
    while (!is_prime_num(num))
        num += 1;

    return num;
}
