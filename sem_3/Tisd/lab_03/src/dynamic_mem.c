#include "dynamic_mem.h"
#include "matrix_struct.h"
#include "exit_code.h"

matrix_data_t create_matrix(size_t n, size_t m)
{
    matrix_data_t matrix = malloc(n * sizeof(int*));
    if (!matrix)
    {
        return NULL;    
    }

    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = calloc(m, sizeof(int));
        if (!matrix[i])
        {
            free_matrix(&matrix, i);
            return NULL;
        }
    }
    
    return matrix;
}

void free_matrix(matrix_data_t *matrix, size_t n)
{
    if (*matrix == NULL)
        return;
    
    for (size_t i = 0; i < n; i++)
    {
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
    }
        
    
    free(*matrix);
    *matrix = NULL;
}

int create_dim_data(dim_data_t *data, size_t len)
{
    data->value = NULL;
    data->ind = NULL;
    data->len = len;

    data->value = malloc(len * sizeof(int));
    if (!data->value)
        return MEM_ERROR;
    
    data->ind = malloc(len * sizeof(size_m));
    if (!data->ind)
        return MEM_ERROR;

    return OK;
}

void free_matrix_razr(matrix_t *m)
{
    if (!m->values && !m->ind && !m->dim)
        return;
        
    free(m->values);
    m->values = NULL;
    
    free(m->ind);
    m->ind = NULL;
        
    free(m->dim);
    m->dim = NULL;
}

void free_dim_data(dim_data_t *data)
{
    if (!data->ind && !data->value)
        return;
    
    free(data->ind);
    data->ind = NULL;
    free(data->value);
    data->value = NULL;
}

