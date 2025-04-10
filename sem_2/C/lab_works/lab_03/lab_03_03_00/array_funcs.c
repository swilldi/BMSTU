#include <stdio.h>
#include "app_errors.h"
#include "array_funcs.h"


// Ввод одномерного массива
int input_array(int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        if (scanf("%d", (arr + i)) != 1)
        {
            return INPUT_ERROR;
        }
    }
    
    return 0;
}

// Вывод одномерного массива
void print_array(const int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
}

// Ввод двухмерного массива
int input_matrix(int (*matrix)[MAX_COLUNMS], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
    {
        if (input_array(matrix[i], col) != 0)
        {
            return INPUT_ERROR;
        }
    }

    return 0;
}

// Вывод двухмерного массива
void print_matrix(int (*matrix)[MAX_COLUNMS], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
    {
        print_array(matrix[i], col);
        printf("\n");
    }
}
