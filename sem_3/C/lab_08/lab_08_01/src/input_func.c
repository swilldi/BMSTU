#include "input_func.h"
#include "exit_code.h"
#include "stdio.h"

int input_ulong(size_t *num)
{
    long buff;
    if (scanf("%lu", &buff) != 1)
        return INVALID_NUM;
    if (buff < 0)
        return NEGATIVE_NUM;
    
    *num = buff;
    return OK;
}

int input_matrix_size(size_t *n, size_t *m)
{
    int rc;
    rc = input_ulong(n);
    if (rc != OK)
        return rc;
    if (n == 0)
        return INVALID_NUM;
    
    rc = input_ulong(m);
    if (rc != OK)
        return rc;
    if (n == 0)
        return INVALID_NUM;
    
        return OK;
}

int input_int(int *num)
{
    long buff;
    if (scanf("%lu", &buff) != 1)
        return INVALID_NUM;
    
    *num = buff;
    return OK;
}

int input_matrix(matrix_t matrix, size_t n, size_t m)
{
    int rc;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            rc = input_int(&matrix[i][j]) != OK;
            if (rc != OK)
                return rc;
        }
    }

    return OK;
}
