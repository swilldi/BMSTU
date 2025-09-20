// Приняв с клавиатуры 𝑥 и 𝜀, 0 < 𝜀 ⩽ 1, вывести на экран вычисленное с точно-
// стью1 𝜀приближённое значение 𝑠(𝑥) и точное значение 𝑓(𝑥) функции 𝑓, абсолютную
// ∆ и относительную 𝛿 погрешности:

#include <stdio.h>
#include <math.h>
#define INPUT_ERROR 1



double f(double x)
{
    return pow(M_E, x);
}

double s(double x, double eps)
{
    int fact_ind = 1;
    double value = 1;
    double result = 1;

    while (fabs(value) >= eps)
    {
        value *= x / fact_ind;
        fact_ind++;

        result += value;
    }
    
    return result;
}

int main(void)
{
    double x, eps;
    double f_value, s_value;
    double delta_absolute, delta_relative;

    printf("Entry x: ");
    if (scanf("%lf", &x) != 1)
    {
        return INPUT_ERROR;
    }
    printf("Entry epsilon: ");
    if (scanf("%lf", &eps) != 1 || eps > 1 || eps <= 0)
    {
        return INPUT_ERROR;
    } 

    f_value = f(x);
    s_value = s(x, eps);

    delta_absolute = fabs(f_value - s_value);
    delta_relative = delta_absolute / fabs(f_value);

    printf("\ns(x) = %lf\nf(x) = %lf\ndelta_absolute = %lf\ndelta_relative = %f\n", s_value, f_value, delta_absolute, delta_relative);

    return 0;
}
