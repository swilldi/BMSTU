/*
Принять с клавиатуры величины оснований 𝑎 и 𝑏 и угла в градусах 𝜙 при боль-
шем основании равнобедренной трапеции. Найти и вывести на экран площадь
𝑆 трапеции.
*/

#include <stdio.h>
#include <math.h>

int main()
{
    float a, b, alpha;
    
    printf("Max side [a]: ");
    scanf("%f", &a);

    printf("Min side [b]: ");
    scanf("%f", &b);
    
    printf("Ugol (degree) [alpha]: ");
    scanf("%f", &alpha);

    double S = (a + b) * (a - b) / 4 * tan(alpha * 3.14 / 180);
    
    printf("S = %.6f", S);
    // printf("%.6f", S);
    return 0;
}