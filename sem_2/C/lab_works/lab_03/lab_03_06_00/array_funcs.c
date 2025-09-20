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
    size_t c = 0;
    while (c < col)
    {
        size_t r = 0;
        for (; r < row; r++)
        {
            if (scanf("%d", &matrix[r][c]) != 1)
            {
                return INPUT_ERROR;
            }
        }

        c++;
        if (c == col)
        {
            return 0;
        }

        r--;
        for (; r < 10; r--)
        {
            if (scanf("%d", &matrix[r][c]) != 1)
            {
                return INPUT_ERROR;
            }
        }
        
        c++;
    }

    return 0;
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
