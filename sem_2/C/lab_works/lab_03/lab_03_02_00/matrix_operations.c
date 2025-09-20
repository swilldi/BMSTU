#include <stdlib.h>
#include <math.h>
#include "array_funcs.h"

int check_row(int *row, size_t len, short digit)
{
    short start_count = 0, end_count = 0;
    for (size_t i = 0; i < len; i++)
    {
        int num = abs(row[i]);

        // if (num > -10 && num < 10)
        // {
        //     continue;
        // }
        
        if (num / (int)pow(10, (int)log10(num)) == digit)
        {
            start_count++;
        }
        else if (num % 10 == digit)
        {
            end_count++;
        }
    }

    return start_count == end_count && start_count != 0 ? 1 : 0;
}

void copy_array(int *arr_1, int *arr_2, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        arr_2[i] = arr_1[i];
    }
}

void set_special_row(int *arr, size_t col)
{
    for (size_t i = 0; i < col; i++)
    {
        arr[i] = 100;
    }
}

size_t action(int (*matrix)[MAX_COLUNMS], size_t rows, size_t columns, short digit)
{
    size_t add_count = 0;
    int indexes[MAX_ROWS / 2];

    // ищем строки, которые удов-ют условию
    for (size_t i = 0; i < rows; i++)
    {
        if (check_row(matrix[i], columns, digit))
        {
            indexes[add_count] = i;
            add_count++;
        }
    }

    if (add_count == 0)
    {
        return rows;
    }

    size_t new_rows = rows + add_count;

    // вставляем строки из чисел 100
    int special_row[MAX_COLUNMS];
    add_count--;
    set_special_row(special_row, columns);
    size_t new_i = new_rows - 1;
    for (size_t i = rows - 1; i < 11; i--)
    {
        if (add_count < 10 && (int)i == indexes[add_count])
        {
            copy_array(special_row, matrix[new_i--], columns); 
            add_count--;
        }
        copy_array(matrix[i], matrix[new_i--], columns);
    }

    return new_rows;
}
