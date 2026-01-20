#include <math.h>
#include <stdio.h>
#define INPUT_ERROR 1
#define TREANGLE_ERROR 2
#define EPS 0.00001

// Возвращает угол между сторонами a и b
float get_angel(float a, float b, float c)
{
    return (float)(pow(c, 2) + pow(b, 2) - pow(a, 2)) / (2 * b * c);
}

// Возвращает длину стороны по двум точкам
float get_side(float x_a, float y_a, float x_b, float y_b)
{
    return (float)sqrt(pow(x_a - x_b, 2) + pow(y_a - y_b, 2));
}

// Проверка возможности существования треугольника
int is_triangle(float a, float b, float c)
{
    return (a + b > c && a + b > c && b + c > a);
}

int main(void)
{
    // обявление переменных
    float x_a, y_a, x_b, y_b, x_c, y_c;
    float ab, bc, ac;
    float angle;
    int type_of_triangel;

    // Ввод данных
    printf("Entyr x_a and y_a: ");
    if (scanf("%f%f", &x_a, &y_a) != 2)
    {
        return INPUT_ERROR;
    }
    printf("Entyr x_b and y_b: ");
    if (scanf("%f%f", &x_b, &y_b) != 2)
    {
        return INPUT_ERROR;
    }
    printf("Entyr x_c and y_c: ");
    if (scanf("%f%f", &x_c, &y_c) != 2)
    {
        return INPUT_ERROR;
    }

    // считаем стороны
    ab = get_side(x_a, y_a, x_b, y_b);
    bc = get_side(x_b, y_b, x_c, y_c);
    ac = get_side(x_a, y_a, x_c, y_c);

    // проверка существования треугольника
    if (!is_triangle(ab, bc, ac))
    {
        return TREANGLE_ERROR;
    }

    // определяем максимальный угол
    if (ab >= bc && ab >= ac)
    {
        angle = get_angel(ab, bc, ac);
    }
    else if (bc >= ab && bc >= ac)
    {
        angle = get_angel(bc, ab, ac);
    }
    else
    {
        angle = get_angel(ac, ab, bc);
    }

    // printf("\n%f | %f | %f", ab, bc, ac);
    // printf("\n%f", angle);
    // определяем тип треугольника
    if (fabs(angle) < EPS)
    {
        type_of_triangel = 1;
    }
    else if (angle > 0)
    {
        type_of_triangel = 0;
    }
    else
    {
        type_of_triangel = 2;
    }

    printf("type of triangel: %d", type_of_triangel);

    return 0;
}
