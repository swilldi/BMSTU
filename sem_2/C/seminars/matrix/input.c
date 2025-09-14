#include <stdio.h>

#define MAX_ROW 10
#define MAX_COL 10

#define INPUT_ERROR 1
#define OUT_OF_RANGE 2
#define OK 0

int input_matrix(int (*m)[MAX_COL], size_t *row, size_t *col)
{
    printf("Максимальный размер матрицы 10x10\n");
    printf("Введите кол-во строк и столбцов через пробел:\n");
    if (scnaf("%zu", row) != 1 || scnaf("%zu", col) != 1)
    {
        return INPUT_ERROR;
    }

    if (*row > MAX_ROW || *row < 1 || *col > MAX_COL || *col < 1 )
    {
        return OUT_OF_RANGE;
    }

    for (size_t i = 0; i < *row; i += 1)
    {
        for (size_t j = 0; j < *col; j += 1)
        {
            if (scnaf("%d", &m[i][j]) != 1)
            {
                return INPUT_ERROR;
            }
        }
    }
    
    return OK;
}