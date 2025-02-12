/*
    Ввод:
    V1 - число литров 1-й емкости
    T1 - темпиратура 1-й емкости
    V2 - число литров 2-й емкости
    T2 - темпиратура 2-й емкости
    
    Вывод:
    V - число литров смешанной смеси
    T - темпиратура смешанной смеси
*/

#include <stdio.h>

int main()
{
    float V1, V2, T1, T2, V, T;
    
    printf("Temperature_1 [T1]: ");
    scanf("%f", &T1);
    
    printf("Volume_1 [V1]: ");
    scanf("%f", &V1);

    printf("Temperature_2 [T2]: ");
    scanf("%f", &T2);
    
    printf("Volume_2 [V2]: ");
    scanf("%f", &V2);

    V = V1 + V2;
    T = (V1 * T1 + V2 * T2) / V;

    printf("V = %.6f | T = %.6f\n", V, T);

    return 0;
}