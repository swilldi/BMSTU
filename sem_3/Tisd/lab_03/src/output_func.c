#include "matrix_struct.h"
#include <stdio.h>
#include "output_func.h"

#include <stdbool.h>

void print_matrix(matrix_data_t matrix, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

size_t contain_num(int *pb, int *pe, int value)
{
    for (int *pc = pb; pc != pe; pc++)
    {
        if (*pc == value)
            return pe - pb;
    }
        
    return (size_t)-1;
}

void print_razr_debug(matrix_t *mtr)
{
    size_t elem_count, dim_len;
    if (mtr->type == csr)
    {
        elem_count = mtr->dim[mtr->n - 1];
        dim_len = mtr->n;
    }
    else
    {
        elem_count = mtr->dim[mtr->m - 1];
        dim_len = mtr->m;
    }

    for (size_t i = 0; i < elem_count; i++)
    {
        printf("%3d ", mtr->ind[i]);
    }
    printf("\n");

    for (size_t i = 0; i < elem_count; i++)
    {
        printf("%3d ", mtr->values[i]);
    }
    printf("\n");

    
    
    for (size_t i = 0; i < dim_len; i++)
    {
        printf("%3d ", mtr->dim[i]);
    }
    printf("\n");

}

void print_csr_matrix(matrix_t *mtr)
{
    size_t ind = 0, len;
    for (size_t i = 0; i < mtr->n; i++)
    {
        if (i != 0)
            len = mtr->dim[i] - mtr->dim[i - 1];
        else
            len = mtr->dim[i];

        size_t i_in_row = mtr->ind[ind];
        for (size_t j = 0; j < mtr->m; j++)
        {
            if (len && i_in_row == j)
            {
                printf("%5d", mtr->values[ind]);
                ind++;
                len--;
                i_in_row = mtr->ind[ind];
            }
            else
            {
                printf("%5d", 0);
            }
        }
        ind = mtr->dim[i];
        printf("\n");
    }
}
