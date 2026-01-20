#include "matrix_func.h"
#include "dynamic_matrix.h"
#include "exit_code.h"
#include "stdbool.h"
#include <math.h>
#include <string.h>


void set_matrix_col(matrix_t mtr, row_col_t col, size_t n, size_t i_col)
{
    for (size_t i = 0; i < n; i++)
        mtr[i][i_col] = col[i];
}

void copy_matrix(matrix_t new_mtr, matrix_t origin_mtr, size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            new_mtr[i][j] = origin_mtr[i][j];
}

error solve_slae_gauss(double **a, double *f, double *x, int n)
{
    int i, j, row;
    double *ptmp;
    double k, tmp;

    matrix_t mtr = create_matrix(n, n);
    if (!mtr)
        return MEM_ERR;

    copy_matrix(mtr, a, n, n);
    double *mtr_data_source = mtr[0];

    for (row = 0; row < n; row++)
    {
        // поиск строки с максимальным элементом в i-м столбце
        int max_row = row;
        for (i = row + 1; i < n; i++)
        {
            if (fabs(mtr[i][row]) > fabs(mtr[max_row][row]))
            {
                max_row = i;
            }
        }

        // максимальный элементов не нулевой
        if (fabs(mtr[max_row][row]) < 1e-9)
        {
            mtr[0] = mtr_data_source;
            free_matrix(mtr);
            return ZERO_MATRIX;
        }

        // меняем строки
        if (max_row != row)
        {
            ptmp = mtr[row];
            mtr[row] = mtr[max_row];
            mtr[max_row] = ptmp;

            tmp = f[row];
            f[row] = f[max_row];
            f[max_row] = tmp;
        }

        // зануляем элементы под строкой
        for (i = row + 1; i < n; i++)
        {
            k = mtr[i][row] / mtr[row][row];
            for (j = row; j < n; j++)
            {
                mtr[i][j] -= k * mtr[row][j];
            }
            f[i] -= k * f[row];
        }
    }

    // заполняем массив с неизветными элементами
    for (i = n - 1; i >= 0; i--)
    {
        tmp = f[i];
        for (j = i + 1; j < n; j++)
        {
            tmp -= mtr[i][j] * x[j];
        }
        x[i] = tmp / mtr[i][i];
    }

    mtr[0] = mtr_data_source;
    free_matrix(mtr);

    return OK;
}

error inverse_matrix(matrix_t *inv_mtr, matrix_t source_mtr, size_t n)
{
    int rc;
    (*inv_mtr) = create_matrix(n, n);
    if (!(*inv_mtr))
        return MEM_ERR;

    double *f = malloc(n * sizeof(double));
    if (!f)
    {
        free_matrix((*inv_mtr));
        return MEM_ERR;
    }

    double *x = malloc(n * sizeof(double));
    if (!x)
    {
        free(f);
        free_matrix((*inv_mtr));
        return MEM_ERR;
    }

    for (size_t i = 0; i < n; i++)
    {
        memset(f, 0, n * sizeof(double));
        f[i] = 1.0;

        rc = solve_slae_gauss(source_mtr, f, x, n);
        if (rc != OK)
        {
            free(f);
            free(x);
            free_matrix((*inv_mtr));
            return rc;
        }

        set_matrix_col((*inv_mtr), x, n, i);
    }

    free(x);
    free(f);
    return OK;
}

error mult_matrix(matrix_t *res, matrix_t mtr_a, matrix_t mtr_b, size_t n, size_t m, size_t k)
{
    (*res) = create_matrix(n, k);
    if (!(*res))
        return MEM_ERR;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            (*res)[i][j] = 0;
            for (size_t p = 0; p < m; p++)
                (*res)[i][j] += mtr_a[i][p] * mtr_b[p][j];
        }
    }

    return OK;
}

error sum_matrix(matrix_t *res, matrix_t mtr_a, matrix_t mtr_b, size_t n, size_t m)
{
    (*res) = create_matrix(n, m);
    if (!(*res))
        return MEM_ERR;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            (*res)[i][j] = mtr_a[i][j] + mtr_b[i][j];
        }
    }

    return OK;
}
