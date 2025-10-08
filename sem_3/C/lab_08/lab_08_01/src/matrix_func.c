#include "matrix_func.h"
#include "dynamic_matrix.h"
#include "exit_code.h"
#include "stdbool.h"

/*
Удалять строки или столбцы с максимальным элементом в матрице. 
Если обнаружено несколько, считать целевым максимум, 
который был бы встречен первым при обходе по строкам

Добавлять всегда сначала новые строки, потом — столбцы.
Добавлять в новые строки округлённые к нижнему целому средние арифмети-
ческие элементов столбцов.
Добавлять в новые столбцы максимумы по строкам.
*/

void matrix_to_sqr_by_row(matrix_t matrix, size_t n, size_t m, size_t new_n)
{
    int *max_in_rows = malloc(n * sizeof(int));
    if (!max_in_rows)
        return MEM_ERROR;
    bool *removed_rows = calloc(n, sizeof(bool));
    if (!removed_rows)
    {
        free(max_in_rows);
        return MEM_ERROR;
    }
        

    // максимумы в строках
    for (size_t i = 0; i < n; i++)
    {
        int max = matrix[i][0];
        // поиск первого максимума
        for (size_t j = 0; j < n; j++)
        {
            if (matrix[i][j] > max)
                max = matrix[i][j];
        }
        max_in_rows[i] = max;
    }

    // поиск n - m максимумов
    for (size_t i = 0; i < n - m; i++)
    {
        size_t ind_max = 0;
        int max = max_in_rows[0];
        // поиск i-го максимума
        for (size_t j = 0; j < n; j++)
        {
            if (removed_rows[j])
                continue;

            if (max_in_rows[j] > max)
            {
                max = max_in_rows[j];
                ind_max = j;
            }
        }
        removed_rows[ind_max] = true;
    }

    // удаление строк
    size_t shift = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (removed_rows[i])
        {
            shift++;
            continue;
        }
        matrix[i - shift] = matrix[i];
    }

    free(removed_rows);
    free(max_in_rows);
}

void matrix_to_sqr_by_col(matrix_t matrix, size_t n, size_t m, size_t new_n)
{
    int *max_in_cols = malloc(m * sizeof(int));
    if (!max_in_rows)
        return MEM_ERROR;
    bool *removed_cols = calloc(m, sizeof(bool));
    if (!removed_rows)
    {
        free(max_in_cols);
        return MEM_ERROR;
    }
        

    // максимумы в колонках
    for (size_t i = 0; i < m; i++)
    {
        int max = matrix[0][i];
        for (size_t j = 0; j < n; j++)
        {
            if (matrix[i][j] > max)
                max = matrix[i][j];
        }
        max_in_rows[i] = max;
    }

    // поиск m - n максимумов
    for (size_t i = 0; i < m - n; i++)
    {
        size_t ind_max = 0;
        int max = max_in_rows[0];
        // поиск i-го максимума
        for (size_t j = 0; j < m; j++)
        {
            if (removed_cols[j])
                continue;

            if (max_in_cols[j] > max)
            {
                max = max_in_cols[j];
                ind_max = j;
            }
        }
        removed_cols[ind_max] = true;
    }

    // удаление столбцов
    size_t shift = 0;
    for (size_t i = 0; i < m; i++)
    {
        if (removed_cols[i])
        {
            shift++;
            continue;
        }
        copy_col(matrix, n, i - shift, i);
    }

    free(removed_cols);
    free(max_in_cols);
}

void copy_col(matrix_t matirx, size_t n, size_t i_to, size_t i_from)
{
    for (size_t i = 0; i < n; i++)
        matrix[i][i_to] = matrix[i][i_from];
}


matrix_t expand_matrix(matrix_t, size_t new_n);


matrix_t transpose_matrix(matrix_t origin, size_t n, size_t m)
{
    matrix_t res = create_matrix(m, n);
    if (!res)
        return NULL;
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            res[j][i] = origin[i][j];
        }
    }

    return res;
}

int mult_row_by_col(int *row, int *col, size_t n)
{
    int res = 0;
    for (size_t i = 0; i < n; i++)
        res += row[i] * col[i];
    
    return res;
}

matrix_t mult_sqr_matrix(matrix_t a, matrix_t b, size_t n)
{
    matrix_t transp_m = transpose_matrix(b, n, n);
    if (!transp_m)
        return NULL;

    matrix_t res = create_matrix(n, n);
    if (!res)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            res[i][j] = mult_row_by_col(a[i], transp_m[j], n);
        }
    }
    
    free(transp_m);
    return res;

}

matrix_t power_sqr_matrix(matrix_t a, size_t n, size_t degree)
{
    matrix_t res = create_matrix(n, n);
    if (degree == 0)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (i == j)
                    res[i][j] = 1;
                else
                    res[i][j] = 0;
            }
        }
            
    }
    else
    {
        for (size_t i = degree; i > 0; i--)
        {
            res = mult_sqr_matrix(a, a, n);
        }
    }
    
    return res;
}
