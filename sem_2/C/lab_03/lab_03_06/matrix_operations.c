#include <stdio.h>

#include <stdlib.h>
#include "io_funcs.h"
#include "matrix_operations.h"

void fill_matrix(int (*matrix)[MAX_COLUNMS], size_t rows, size_t columns)
{
    for (size_t col = 0; col < columns; col++)
    {
        for (size_t row = 0; row < rows; row++)
        {
            short value = col * rows + (row + 1);
            // printf("%zu * %zu + %zu + 1 = %d\n", col, rows, row, value);
            if (col % 2 == 0)
            {
                matrix[row][col] = value;
            }
            else
            {
                matrix[rows - row - 1][col] = value;
            }
        }
    }
}
