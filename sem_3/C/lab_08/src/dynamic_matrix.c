#include "stdlib.h"
#include <dynamic_matrix.h>

matrix_t create_matrix(size_t n, size_t m)
{
    matrix_t mtr = malloc(n * sizeof(double *));
    if (!mtr)
        return NULL;

    double *data = malloc(n * m * sizeof(double));
    if (!data)
    {
        free(mtr);
        return NULL;
    }

    for (size_t i = 0; i < n; i++)
        mtr[i] = data + i * m;

    return mtr;
}

void free_matrix(matrix_t mtr)
{
    free(mtr[0]);
    free(mtr);
}
