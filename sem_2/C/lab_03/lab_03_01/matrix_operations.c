#include <stdlib.h>
#include <math.h>
#include "io_funcs.h"

void check_columns(int (*matrix)[MAX_COLUNMS], size_t rows, size_t colunms, int *arr)
{
    // выбираем столбце
    for (size_t col = 0; col < colunms; col++)
    {
        int value = rows == 1 ? 0 : 1;
        // проверяем элементы столбца
        for (size_t row = 0; row < rows - 1; row++)
        {
            if (matrix[row][col] <= matrix[row + 1][col])
            {
                value = 0;
                break;
            }
        }
        arr[col] = value;
    }
}
