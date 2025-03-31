/*
Принять с клавиатуры величины оснований 𝑎 и 𝑏 и высоты ℎ равнобедренной
трапеции. Найти и вывести на экран периметр 𝑃 трапеции.
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, h;
    float hip, p;

    printf("Enter a: ");
    scanf("%f", &a);

    printf("Enter b: ");
    scanf("%f", &b);

    printf("Enter h: ");
    scanf("%f", &h);

    hip = sqrt(pow((a - b) / 2, 2) + pow(h, 2));
    p = a + b + 2 * hip;
    printf("P = %f \n", p);
    return 0;
}
