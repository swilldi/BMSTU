/*
min(a_0 * a_1, a_1 * a_2, ..., a_(n-2) * a_(n-1))
*/

#include <stdio.h>

#define MAX_SIZE 10
#define INPUT_ERROR 1
#define INPUT_ERROR_MESSAGE "Input is invalid"
#define OUT_OF_RANGE 2
#define OUT_OF_RANGE_MESSAGE "Length is out of range (Valid range 1-10)"
#define IMPOSSIABLE_SOLVE 3
#define IMPOSSIABLE_SOLVE_MESSAGE "Impossable solve"



int find_min(int *current, int *end, int *result)
{
    if (current + 1 >= end)
    {
        // *result_code = IMPOSSIABLE_SOLVE;
        return 1;
    }

    int min = *current * *(current + 1), value;
    for (; current + 1 < end; current++)
    {
        value = *current * *(current + 1);
        if (value < min) 
        {
            min = value;
        }
    }
    
    *result = min;

    return 0;
}

int input_arr(int *current, int *end)
{
    for (; current < end; current++)
    {
        printf("Entry element: ");
        if (scanf("%d", current) != 1)
        {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    int array[MAX_SIZE];
    int len;

    printf("Entry length: ");
    
    // не число
    if (scanf("%d", &len) != 1)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    // недопустимое значение для длины
    if (len > 10 || len < 0)
    {
        printf(OUT_OF_RANGE_MESSAGE);
        return OUT_OF_RANGE;
    }

    // // невозможно вычислить ответ 
    // if (len < 2)
    // {
    //     printf(IMPOSSIABLE_SOLVE_MESSAGE);
    //     return IMPOSSIABLE_SOLVE;
    // }

    // ввод массива
    if (input_arr(array, (array + len)) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    int min;
    int code = find_min(array, (array + len), &min);
    if (code != 0)
    {
        printf(IMPOSSIABLE_SOLVE_MESSAGE);
        return IMPOSSIABLE_SOLVE;
    }

    printf("%d", min);

    return 0;
}
