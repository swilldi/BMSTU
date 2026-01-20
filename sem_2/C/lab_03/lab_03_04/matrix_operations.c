#include <stdlib.h>
#include <math.h>
#include "io_funcs.h"

int find_min(int (*matrix)[MAX_COLUNMS], size_t size, int *min)
{
    *min = 0;
    short found = 0;

    for (size_t row = 1; row < size; row++)
    {
        for (size_t col = 0; col < row; col++)
        {
            if (abs(matrix[row][col]) % 2 != 0 && (matrix[row][col] < *min || !found))
            {
                *min = matrix[row][col];
                found = 1;
            }
        }
    }

    return found;
}
