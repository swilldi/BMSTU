/*
Сформировать и вывести на экран новый массив, в который сначала скопиро-
вать элементы исходного массива, большие среднего арифметического
*/

#include <stdio.h>
#define INPUT_ERROR 1
#define EMPTY_ARRAY_ERROR 2
#define OUT_OF_RANGE 3
#define INPUT_ERROR_MESSAGE "Error: not a number entered\n"
#define EMPTY_ARRAY_ERROR_MESSAGE "Error: array is empty\n"
#define OUT_OF_RANGE_MESSAGE "Error: number greater then ten or negative\n"

int input_arr(int arr[], size_t length)
{
    int num;
    for (size_t i = 0; i < length; i++)
    {
        printf("Entry element: ");
        if (scanf("%d", &num) != 1)
        {
            return INPUT_ERROR;
        }
        arr[i] = num;
    }

    return 0;
}

int sum_elements(int arr[], size_t length)
{
    int sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    return sum;
}

void print_arr(int arr[], size_t length)
{
    printf("|");
    for (size_t i = 0; i < length; i++)
    {
        printf(" %d |", arr[i]);
    }
    printf("\n");
}

size_t greater_arith_mean(int *arr, int *arr_new, size_t length)
{
    float arith_mean = (float)sum_elements(arr, length) / length;
    size_t new_i = 0;

    // заполняем новый массива числами > ср.ариф
    for (size_t i = 0; i < length; i++)
    {
        if (arr[i] > arith_mean)
        {
            arr_new[new_i] = arr[i];
            new_i++;
        }
    }
    return new_i;
}

int main(void)
{
    int arr[10], arr_new[10];
    size_t length, new_i;

    // ввод длины массива
    printf("Entry length of array: ");
    if (scanf("%lu", &length) != 1)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (length > 10)
    {
        printf(OUT_OF_RANGE_MESSAGE);
        return OUT_OF_RANGE;
    }

    // заполнение массива
    if (input_arr(arr, length) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    } 

    // обработка деления на ноль
    if (length == 0)
    {
        printf(EMPTY_ARRAY_ERROR_MESSAGE);
        return EMPTY_ARRAY_ERROR;
    }

    new_i = greater_arith_mean(arr, arr_new, length);

    // выводим элементы массива
    if (new_i != 0) 
    {
        print_arr(arr_new, new_i);
    }
    else 
    {
        printf(EMPTY_ARRAY_ERROR_MESSAGE);
        return EMPTY_ARRAY_ERROR;
    }
    

    return 0;
}
