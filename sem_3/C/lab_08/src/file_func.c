#include "file_func.h"
#include "dynamic_matrix.h"
#include "exit_code.h"
#include "input_func.h"
#include "stdio.h"
#include <stdbool.h>

error check_file(FILE *f)
{
    if (!f)
        return FILE_OPEN_ERR;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (size == 0)
        return FILE_EMPTY_ERR;

    return OK;
}

error read_full_matrix(FILE *f, matrix_t *mtr, size_t *n, size_t *m)
{
    int rc;

    rc = read_matrix_sizes(f, n, m);
    if (rc != OK)
        return rc;

    (*mtr) = create_matrix(*n, *m);
    if (!(*mtr))
    {
        rc = MEM_ERR;
        return rc;
    }
    rc = read_matrix(f, (*mtr), *n, *m);
    if (rc != OK)
    {
        free_matrix((*mtr));
        return rc;
    }

    return OK;
}

error read_matrix(FILE *f, matrix_t mtr, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (fscanf(f, "%lf", &mtr[i][j]) != 1)
                return IO_ERR;
        }
    }

    return OK;
}

error read_matrix_sizes(FILE *f, size_t *n, size_t *m)
{
    int tmp_n, tmp_m;

    if (fscanf(f, "%d%d", &tmp_n, &tmp_m) != 2)
        return IO_ERR;
    if (tmp_n <= 0 || tmp_m <= 0)
        return RANGE_ERR;

    *n = (size_t)tmp_n;
    *m = (size_t)tmp_m;
    return OK;
}

void write_matrix(FILE *f, matrix_t mtr, size_t n, size_t m)
{
    fprintf(f, "%zu %zu\n", n, m);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            fprintf(f, "%lf ", mtr[i][j]);
        }
        fprintf(f, "\n");
    }
}
