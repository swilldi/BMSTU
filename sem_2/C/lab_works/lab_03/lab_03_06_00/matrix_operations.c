#include <stdlib.h>
#include "io_funcs.h"

// Ввод двухмерного массива
void fill_matrix(int (*matrix)[MAX_COLUNMS], size_t row, size_t col)
{
    size_t c = 0;
    short down = 1;
    while (c < col)
    {
        for (size_t r = 0; r < row; r++)
        {
            r = down ? r : (row - r - 1);
            matrix[r][c] = row * c + r;
        }
        down = down ? 0 : 1;
        c++;
    }
}
