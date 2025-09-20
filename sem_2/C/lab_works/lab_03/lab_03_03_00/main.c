/*
сортировка строк массива по сумме элементов по возрастанию
*/

#include <stdio.h>
#include "array_funcs.h"
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
    size_t rows, columns;
    int matrix[MAX_ROWS][MAX_COLUNMS];

    // ввод кол-ва строк
    printf("Entry amount of rows: ");
    if (input_length(&rows) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    // ввод кол-ва колонок
    printf("Entry amount of colunms: ");
    if (input_length(&columns) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (rows == 0 || columns == 0)
    {
        printf(IMPOSSABLE_SOLVE_MESSAGE);
        return IMPOSSABLE_SOLVE;
    }

    // ввод матрицы
    if (input_matrix(matrix, rows, columns) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    sort(matrix, rows, columns);

    print_matrix(matrix, rows, columns);
}
