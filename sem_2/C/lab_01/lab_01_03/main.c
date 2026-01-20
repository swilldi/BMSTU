/*
Ввод:
h – рост человека
t – обхват грудной клетки
m – вес в килограммах

Вывод:
нормальный вес
индекс массы тела
*/

#include <stdio.h>

int main(void)
{
    float h, t, m;
    float m_normal, bmi;

    printf("Height: ");
    scanf("%f", &h);

    printf("Chest circumference: ");
    scanf("%f", &t);

    printf("Weight: ");
    scanf("%f", &m);

    m_normal = h * t / 240;

    h /= 100;
    bmi = m / h / h;

    printf("m_noraml = %f \nBMI = %f \n", m_normal, bmi);
    return 0;
}
