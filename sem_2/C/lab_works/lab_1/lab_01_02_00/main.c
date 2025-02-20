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

    // ввод основания a
    printf("Enter a: ");
    scanf("%f", &a);

    // ввод основания b
    printf("Enter b: ");
    scanf("%f", &b);

    // ввод высоты
    printf("Enter h: ");
    scanf("%f", &h);

    // произведение расчетов
    hip = sqrt(pow((a - b) / 2, 2) + pow(h, 2));
    P = a + b + 2 * hip;

    // вывод периметра
    printf("P = %f \n", P);
    return 0;
}
