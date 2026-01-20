/*
Вывести одномерный массив и его k-тому элементу присвоить 1, если условие
выполнено, в противном случае 0

Элементы k-го столбца упорядочены по убыванию
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
    size_t rows, columns;
    int matrix[MAX_ROWS][MAX_COLUNMS];
    int array[MAX_COLUNMS];

    // ввод кол-ва строк
    printf("Entry amount of rows: ");
    if (input_length(&rows) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (rows > MAX_ROWS)
    {
        printf(OUT_OF_RANGE_MESSAGE);
        return OUT_OF_RANGE;
    }

    // ввод кол-ва колонок
    printf("Entry amount of colunms: ");
    if (input_length(&columns) != 0)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (columns > MAX_COLUNMS)
    {
        printf(OUT_OF_RANGE_MESSAGE);
        return OUT_OF_RANGE;
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

    check_columns(matrix, rows, columns, array);

    print_array(array, columns);
}
