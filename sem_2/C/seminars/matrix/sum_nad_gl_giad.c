#include <stdio.h>

#define MAX_COL
#define NOT_SQR_MAXTRIX 3

int sum_over_main_diag(int (*m)[MAX_COL], size_t row, size_t col, int *sum)
{
    if (row != col) 
    { 
        return NOT_SQR_MAXTRIX; 
    }
    
    *sum = 0;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = i; j < col; j++)
        {
            ;
        }
    }
    return 0;
}