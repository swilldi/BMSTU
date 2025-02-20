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
    
    // Ввод роста
    printf("Height: ");
    scanf("%f", &h);

    // Ввод роста обхват грудной клетки
    printf("Chest circumference: ");
    scanf("%f", &t);

    // Ввод веса
    printf("Weight: ");
    scanf("%f", &m);
    
    // Вычисление номального веса
    m_normal = h * t / 240;

    // Вычисление IMB
    h /= 100;
    bmi = m / h / h;

    // Вывод IMB и нормального веса
    printf("m_noraml = %f \nBMI = %f \n", m_normal, bmi);
    return 0;
}
