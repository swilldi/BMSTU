#include <stdio.h>
#include "app_errors.h"
#include "io_funcs.h"

// Вывод одномерного массива
void print_array(const int *arr, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
}

// Вывод двухмерного массива
void print_matrix(int (*matrix)[MAX_COLUNMS], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            printf("%d ", matrix[i][j]);
        } 
        printf("\n");
    }
}
