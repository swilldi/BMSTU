#include <stdio.h>

#define MAX_ROW 10
#define MAX_COL 10
#define NOT_SQR_MAXTRIX 3

#define INPUT_ERROR 1
#define OUT_OF_RANGE 2
#define OK 0

int input_matrix(int (*m)[MAX_COL], size_t row, size_t col, int arr[], size_t *len)
{
    if (row != col) { return NOT_SQR_MAXTRIX; }

    *len = row * 2;
    
    for (size_t i = 0; i < row; i++)
    {
        arr[i] = m[i][i];
        arr[i + row - 1] = m[i][row - i - 1];
    }

    return OK;
}