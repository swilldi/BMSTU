#include <stdlib.h>
#include <math.h>
#include "io_funcs.h"


int is_prime(int num)
{
    if (num <= 1)
    {
        return 0;
    }
    for (int d = 2; d <= sqrt(num); d++)
    {
        if (num % d == 0)
        {
            return 0;
        }
    }
    return 1;
}

void reverse_array(int arr[], size_t len)
{
    int memory;
    for (size_t i = 0; i < len / 2; i++)
    {
        memory = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = memory;
    }
}

int reverse_prime_num(int (*matrix)[MAX_COLUNMS], size_t rows, size_t colunms)
{
    int prime_numbers[MAX_COLUNMS * MAX_ROWS];
    int indexes[MAX_COLUNMS * MAX_ROWS][2];
    size_t count_prime = 0;
    
    // расположение простых чисел и их значения
    for (size_t row = 0; row < rows; row++)
    {
        for (size_t col = 0; col < colunms; col++)
        {
            if (is_prime(matrix[row][col]))
            {
                prime_numbers[count_prime] = matrix[row][col];
                indexes[count_prime][0] = row;
                indexes[count_prime][1] = col;
                count_prime++;
            }
        }
    }

    if (count_prime == 0)
    {
        return 1;
    }

    reverse_array(prime_numbers, count_prime);

    // заполнение по новой
    for (size_t i = 0; i < count_prime; i++)
    {
        int r = indexes[i][0];
        int c = indexes[i][1];

        matrix[r][c] = prime_numbers[i];
    }

    return 0;
}

