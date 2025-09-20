#include <stdlib.h>
#include <math.h>
#include "array_funcs.h"

void action(int (*matrix)[MAX_COLUNMS], size_t rows, size_t colunms, int *arr)
{
    for (size_t k = 0; k < colunms; k++)
    {
        int is_decreasing = 1;
        for (size_t i = 0; i < rows - 1; i++)
        {
            if (matrix[i][k] <= matrix[i + 1][k])
            {
                is_decreasing = 0;
                break;
            }
        }
        arr[k] = is_decreasing ? 1 : 0;
    }
}
