#include "matrix_struct.h"
#include "matrix_func.h"
#include "exit_code.h"
#include "dynamic_mem.h"
#include <stdlib.h>



int extract_matrix_values(matrix_t *matrix)
{
    matrix->max_values *= 2;
    
    int *tmp = realloc(matrix->values, matrix->max_values * sizeof(int));
    if (!tmp)
        return MEM_ERROR;

    matrix->values = tmp;

    tmp = realloc(matrix->ind, matrix->max_values * sizeof(size_m));
    if (!tmp)
        return MEM_ERROR;

    matrix->ind = (unsigned int*)tmp;

    return OK;
}



int matrix_to_csr(matrix_t *m_csr, matrix_data_t mtr, size_m n, size_m m)
{
    int rc;
    rc = create_matrix_razr(m_csr, n, m, TYPE_CSR);
    if (rc != OK)
        return rc;

    size_t num_count = 0;
    for (size_t i = 0; i < n; i++)
    {   
        for (size_t j = 0; j < m; j++)
        {
            if (mtr[i][j] == 0)
                continue;

            // количество чисел превышает выделенное количество
            if (num_count >= m_csr->max_values)
            {
                rc = extract_matrix_values(m_csr);
                if (rc != OK)
                    return rc;
            }
            
            // запись данного числа
            m_csr->values[num_count] = mtr[i][j];
            m_csr->ind[num_count] = j;
            num_count++;
        }
        // запись количество встреченных чисел до i-й строки
        m_csr->dim[i] = num_count;
    }
    
    return OK;
}

int matrix_to_csc(matrix_t *m_csr, matrix_data_t mtr, size_m n, size_m m)
{
    int rc;
    rc = create_matrix_razr(m_csr, n, m, TYPE_CSC);
    if (rc != OK)
        return rc;    

    size_t num_count = 0;
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (mtr[j][i] == 0)
                continue;

            // количество чисел превышает выделенное количество
            if (num_count >= m_csr->max_values)
            {
                rc = extract_matrix_values(m_csr);
                if (rc != OK)
                    return rc;
            }
            
            // запись данного числа
            m_csr->values[num_count] = mtr[j][i];
            m_csr->ind[num_count] = j;
            num_count++;
        }
        // запись количество встреченных чисел до i-й строки
        m_csr->dim[i] = num_count;
    }
    
    return OK;
}

int mult_row_by_col(dim_data_t *d_a, dim_data_t *d_b)
{
    int res = 0;
    size_t i = 0, j = 0;

    // предполагаем, что индексы отсортированы по возрастанию
    while (i < d_a->len && j < d_b->len)
    {
        if (d_a->ind[i] == d_b->ind[j])
        {
            res += d_a->value[i] * d_b->value[j];
            i++;
            j++;
        }
        else if (d_a->ind[i] < d_b->ind[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    return res;
}


// #include <stdio.h>
int mult_csr_by_csc(matrix_t *mtr, matrix_t *m_csr, matrix_t *m_csc)
{
    int rc;
    rc = create_matrix_razr(mtr, m_csr->n, m_csc->m, TYPE_CSR);
    if (rc != OK)
        return rc;

    dim_data_t row, col;
    rc = create_dim_data(&row, m_csr->m);
    if (rc != OK) 
        return rc;
    rc = create_dim_data(&col, m_csc->n);
    if (rc != OK)
    {
        free_dim_data(&row);
        return rc;
    }

    size_t num_count = 0;

    for (size_t i = 0; i < m_csr->n; i++)
    {
        get_dim_data(&row, m_csr, i);

        for (size_t j = 0; j < m_csc->m; j++)
        {
            get_dim_data(&col, m_csc, j);

            int val = mult_row_by_col(&row, &col);
            if (val == 0)
                continue;

            // проверка необходимости расширить массив
            if (num_count >= mtr->max_values)
            {
                rc = extract_matrix_values(mtr);
                if (rc != OK)
                {
                    free_dim_data(&row);
                    free_dim_data(&col);
                    return rc;
                }
            }

            mtr->values[num_count] = val;
            mtr->ind[num_count] = j;
            num_count++;
        }

        mtr->dim[i] = num_count;
    }

    free_dim_data(&row);
    free_dim_data(&col);

    return OK;
}


void get_dim_data(dim_data_t *data, matrix_t *mtr, size_t ind)
{
    size_t len = mtr->dim[ind], shift = 0;
    if (ind != 0)
    {
        len -= mtr->dim[ind - 1];
        shift = mtr->dim[ind - 1];
    }
        
    data->len = len;
    for (size_t i = 0; i < len; i++)
    {
        data->value[i] = mtr->values[shift + i];
        data->ind[i] = mtr->ind[shift + i];
    }
    
}

int classic_mult(matrix_data_t *res, matrix_data_t a, matrix_data_t b, size_t n, size_t m, size_t k)
{
    *res = create_matrix(n, k);
    if (!(*res))
        return MEM_ERROR;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            (*res)[i][j] = 0;
            for (size_t common_i = 0; common_i < m; common_i++)
                (*res)[i][j] += a[i][common_i] * b[common_i][j];
        }
    }

    return OK;
}
