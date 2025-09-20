/*
Ввод:
a – целое
n – целое положительное

Вывод:
a^n
*/

#include <stdio.h>
#define as 1

int my_pow(int a, int n)
{
    int result = a;
    for (int i = 1; i < n; i++)
    {
        result *= a;
    }
    return result;
}

int main(void)
{
    int a, n;
    int result;

    // ввод числа и степени
    printf("Entry num and degree: ");
    int input_result = scanf("%d %d", &a, &n);
    
    // обратока ввода
    if (input_result != 2 || n < 0)
        return 1;
    
    // расчеты
    result = my_pow(a, n);
    
    // вывод a^n
    printf("a^n = %d\n", result);
    return 0;
}
