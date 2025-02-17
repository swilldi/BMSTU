/*
Принять с клавиатуры величины оснований 𝑎 и 𝑏 и высоты ℎ равнобедренной
трапеции. Найти и вывести на экран периметр 𝑃 трапеции.
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, h;
    float hip, P;

    printf("Enter a (max base): ");
    scanf("%f", &a);

    printf("Enter b (min base): ");
    scanf("%f", &b);

    printf("Enter h: ");
    scanf("%f", &h);

    hip = sqrt(pow((a - b) / 2, 2) + pow(h, 2));
    P = a + b + 2 * hip;
    printf("%f", P);
    return 0;
}
