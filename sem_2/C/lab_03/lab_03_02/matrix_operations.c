#include <stdlib.h>
#include <math.h>
#include "io_funcs.h"

#include <stdio.h>


int first_digit(int num)
{
    while (num >= 10)
    {
        num /= 10;
    }
    return num;
}

int last_digit(int num)
{
    return num % 10;
}


int check_row(int *row, size_t len, short digit)
{
    short start_count = 0, end_count = 0;
    for (size_t i = 0; i < len; i++)
    {
        int num = abs(row[i]);
        
        if (first_digit(num) == digit)
        {
            start_count++;
        }
        
        if (last_digit(num) == digit)
        {
            end_count++;
        }
    }

    return start_count == end_count && start_count != 0;
}

void copy_array(int *arr_1, int *arr_2, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        arr_2[i] = arr_1[i];
    }
}

void set_row(int *arr, size_t col, int num)
{
    for (size_t i = 0; i < col; i++)
    {
        arr[i] = num;
    }
}

size_t action(int (*matrix)[MAX_COLUNMS], size_t rows, size_t columns, short digit)
{
    size_t add_rows = 0;
    int index_row[MAX_ROWS] = { 0 };
    for (size_t i = 0; i < rows; i++)
    {
        if (check_row(matrix[i], columns, digit))
        {
            index_row[i] = 1;
            add_rows++;
        }
    }

    if (add_rows == 0)
    {
        return rows;
    }

    int filling_row[MAX_COLUNMS];
    set_row(filling_row, columns, 100);

    size_t new_i = rows + add_rows - 1;
    // printf("\n%zu | %zu\n", new_i, add_rows);

    // for (size_t i = 0; i < MAX_COLUNMS; i++)
    // {
    //     printf("%d ", index_row[i]);
    // }
    // printf("\n");

    for (size_t i = rows - 1; i != (size_t)-1; i--)
    {
        // printf("%zu\n", i);
        if (index_row[i])
        {
            copy_array(filling_row, matrix[new_i], columns);
            copy_array(matrix[i], matrix[new_i - 1], columns);
            new_i--;
        }
        else
        {
            copy_array(matrix[i], matrix[new_i], columns);
        }
        new_i--;
    }

    return rows + add_rows;
}
