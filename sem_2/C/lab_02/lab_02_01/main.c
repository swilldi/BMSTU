#include <stdio.h>
#define INPUT_ERROR 1
#define NOT_VALUE_ERROR 2
#define OUT_OF_RANGE 3
#define INPUT_ERROR_MESSAGE "Error: not a number entered\n"
#define NOT_VALUE_ERROR_MESSAGE "Error: not even numers in array\n"
#define OUT_OF_RANGE_MESSAGE "Error: number greater then ten or negative\n"


int even_sum(int arr[], size_t length, int *sum)
{
    int count_even = 0;
    for (size_t i = 0; i < length; i++)
    {
        if (arr[i] % 2 == 0)
        {
            *sum += arr[i];
            count_even++;
        }
    }
    return count_even ? 0 : NOT_VALUE_ERROR;
}

int input_arr(int arr[], size_t length)
{
    int num;
    for (size_t i = 0; i < length; i++)
    {
        printf("Entry element: ");
        if (scanf("%d", &num) != 1)
        {
            printf(INPUT_ERROR_MESSAGE);
            return INPUT_ERROR;
        }
        arr[i] = num;
    }

    return 0;
}

int main(void)
{
    size_t length;
    int arr[10], result = 0;

    // ввод размера массива
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
    
    // заполнени массива
    if (input_arr(arr, length) != 0)
    {
        return INPUT_ERROR;
    }


    if (even_sum(arr, length, &result) != 0)
    {
        printf(NOT_VALUE_ERROR_MESSAGE);
        return NOT_VALUE_ERROR;
    }
    printf("Sum of even numbers = %d\n", result);

    return 0;
}
