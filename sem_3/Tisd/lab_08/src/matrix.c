#include <stdlib.h>
#include <string.h>
#include "exit_code.h"
#include "matrix.h"
#include <stdio.h>

matrix_t matrix_create(int n, int m)
{
    matrix_t matrix = malloc(sizeof(int*) * n);
    if (matrix)
    {
        for (int i = 0; i < n && matrix; i++)
        {
            matrix[i] = malloc(sizeof(int) * m);
            if (!matrix[i])
            {
                matrix_destoy(matrix, i);
                matrix = NULL;
            }
        }
    }

    return matrix;
}

void matrix_destoy(matrix_t matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

void matrix_print(matrix_t matrix, int n)
{
    int separator_line_len = n * 7 + 10;

    for (int i = 0; i < separator_line_len; i++)
        printf("=");
    printf("\n");

    printf("исх.\\кон.");
    for (int i = 0; i < n; i++)
        printf("| %4d ", i + 1);
    printf("|\n");

    for (int i = 0; i < separator_line_len; i++)
        printf("=");
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%7d ||", i + 1);
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != (unsigned int)-1)
                printf(" %4d |", matrix[i][j]);
            else
                printf(" %4s |", "--");
        }

        // printf("|\n");
        printf("\n");
    }

    for (int i = 0; i < separator_line_len; i++)
        printf("=");
    printf("\n\n");
}
