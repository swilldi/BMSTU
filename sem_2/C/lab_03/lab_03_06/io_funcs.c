#include <stdio.h>
#include "app_errors.h"
#include "io_funcs.h"

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
