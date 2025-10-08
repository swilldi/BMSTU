#include <dynamic_matrix.h>
#include "stdlib.h"

matrix_t create_matrix(size_t n, size_t m)
{
    matrix_t matrix = malloc(n * sizeof(int*));
    if (!matrix)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = calloc(m, sizeof(int));
        if (!matrix[i])
        {
            free_matrix(matrix, i + 1);
            return NULL;
        }
    }
            
     return matrix;   
}


void free_matrix(matrix_t matrix, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(matrix[i]);
    
    free(matrix);
}
