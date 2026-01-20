#include <stdlib.h>
#include <math.h>
#include "io_funcs.h"

void swap_row(int arr_1[MAX_COLUNMS], int arr_2[MAX_COLUNMS], size_t colunms)
{
    for (size_t i = 0; i < colunms; i++)
    {
        int memory_element = arr_1[i];
        arr_1[i] = arr_2[i];
        arr_2[i] = memory_element;
    }
}

void swap_elements(int arr[], size_t i_1, size_t i_2)
{
    int memory_element = arr[i_1];
    arr[i_1] = arr[i_2];
    arr[i_2] = memory_element;
}


void get_sums_of_rows(int (*matrix)[MAX_COLUNMS], size_t rows, size_t colunms, int arr[])
{
    int sum;
    for (size_t row = 0; row < rows; row++)
    {
        sum = 0;
        for (size_t col = 0; col < colunms; col++)
        {
            sum += matrix[row][col];
        }
        arr[row] = sum;
    }
}

void sort(int (*matrix)[MAX_COLUNMS], size_t rows, size_t colunms)
{
    int sums_of_rows[MAX_COLUNMS];
    get_sums_of_rows(matrix, rows, colunms, sums_of_rows);
    
    for (size_t i = 0; i < rows - 1; i++)
    {
        // ищем минимальный элемент в неотсортированной части
        int min_element = sums_of_rows[i], index_min_element = i;
        for (size_t j = i + 1; j < rows; j++)
        {
            if (sums_of_rows[j] < min_element)
            {
                min_element = sums_of_rows[j];
                index_min_element = j;
            }
        }
        
        // совершаем свап
        swap_elements(sums_of_rows, i, index_min_element);
        swap_row(matrix[i], matrix[index_min_element], colunms);
    }
}

