// Приняв с клавиатуры по концевому признаку (до первого отрицательного чис-
// ла) элементы непустой последовательности неотрицательных чисел 𝑥, вычислить и
// вывести на экран значение 𝑔(𝑥)


#include <stdio.h>
#include <math.h>
#define INPUT_ERROR 1

double solve(double x, int n)
{
    return x / (double)n;
}

int main(void)
{
    double x, result = 0;
    int n = 1;

    printf("Entry x: ");
    if (scanf("%lf", &x) != 1 || x < 0)
    {
        return INPUT_ERROR;
    }
    
    while (x >= 0)
    {
        result += solve(x, n);
        n++;

        printf("Entry x: ");
        if (scanf("%lf", &x) != 1)
        {
            return INPUT_ERROR;
        }
    }
    printf("g(x) = %f", sqrt(result));

    return 0;
}
