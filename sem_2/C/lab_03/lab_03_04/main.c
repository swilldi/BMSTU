/*
Найти и вывести на экран минимальное нечётное число, расположенное под
главной диагональю.
*/

#include <stdio.h>
#include "io_funcs.h"
#include "app_errors.h"
#include "matrix_operations.h"

int input_length(size_t *len)
{
    if (scanf("%lu", len) != 1)
    {
        return INPUT_ERROR;
    }
    return 0;
}


int main(void)
{
    size_t size, size_2;
    int matrix[MAX_ROWS][MAX_COLUNMS];

    // ввод кол-ва колонок
    printf("Entry size matrix: ");
    if (input_length(&size) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    printf("Entry size matrix: ");
    if (input_length(&size_2) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (size != size_2)
    {
        printf(NOT_SQUARE_MATRIX_MESSAGE);
        return NOT_SQUARE_MATRIX;
    }

    if (size > MAX_ROWS)
    {
        printf(OUT_OF_RANGE_MESSAGE);
        return OUT_OF_RANGE;
    }

    if (size < 2)
    {
        printf(IMPOSSABLE_SOLVE_MESSAGE);
        return IMPOSSABLE_SOLVE;
    }

    // ввод матрицы
    if (input_matrix(matrix, size, size) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    int min;
    if (find_min(matrix, size, &min) == 0)
    {
        printf(IMPOSSABLE_SOLVE_MESSAGE);
        return IMPOSSABLE_SOLVE;
    }

    printf("Minumal number: %d\n", min);
}
