/*
Вставить строку из чисел 100 после каждой строки, в которой количество эле-
ментов, начинающихся на заданную цифру, равно количеству элементов, за-
канчивающихся на эту же цифру
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
    short digit;

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

    // ввод ключевой цифры 
    printf("Entry digit: ");
    if (scanf("%hd", &digit) != 1)
    {
        printf(INPUT_ERROR_MESSAGE);
        return INPUT_ERROR;
    }

    if (digit > 9 || digit < 0)
    {
        printf(NOT_DIGIT_MESSAGE);
        return NOT_DIGIT_ERROR;
    }

    rows = action(matrix, rows, columns, digit);

    print_matrix(matrix, rows, columns);
}
