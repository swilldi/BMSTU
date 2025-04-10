#include <stdlib.h>
#include <math.h>
#include "array_funcs.h"

int find_min(int (*matrix)[MAX_COLUNMS], size_t size, int *min)
{
    *min = matrix[1][0];
    int min_is_odd = abs(*min) % 2 != 0 ? 1 : 0;

    for (size_t row = 1; row < size; row++)
    {
        for (size_t col = 0; col < row; col++)
        {
            if ((matrix[row][col] < *min || !min_is_odd) && abs(matrix[row][col]) % 2 != 0)
            {
                *min = matrix[row][col];
                min_is_odd = 1;
            }
        }
    }

    return !min_is_odd;
}
