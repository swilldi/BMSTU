#include <stdio.h>

#define MAX_ROW 10
#define MAX_COL 10

void print_matrix(int (*m)[MAX_COL], size_t row, size_t col)
{
    for (size_t r = 0; r < row; r++)
    {
        for (size_t c = 0; c < col; c++)
        {
            printf("%d ", m[r][c]);
        }
        printf("\n");
    }
}