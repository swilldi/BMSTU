#include "matrix_struct.h"
#include "matrix_func.h"
#include "exit_code.h"
#include "dynamic_mem.h"
#include <stdlib.h>

#define START_NUMBER_VALUES 50

int create_matrix_razr(matrix_t *mtr, size_m n, size_m m, type_m type)
{
    mtr->n = n;
    mtr->m = m;
    mtr->type = type;
    mtr->max_values = START_NUMBER_VALUES;
    mtr->values = NULL;
    mtr->ind = NULL;
    mtr->dim = NULL;

    // выделение памяти для значений
    mtr->values = malloc(START_NUMBER_VALUES * sizeof(int));
    if (!mtr->values)
        return MEM_ERROR;

    // выделение памяти для индектос значений в основном измерении
    mtr->ind = malloc(START_NUMBER_VALUES * sizeof(size_m));
    if (!mtr->ind)
    {
        return MEM_ERROR;
    }
        
    // выделение памяти для количества значений в второстепенном измерении
    if (type == csr)
        mtr->dim = malloc(m * sizeof(size_m));
    else
        mtr->dim = malloc(n * sizeof(size_m));
    
    if (!mtr->dim)
    {
        return MEM_ERROR;
    }
    
    return OK;
}

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

int mult_row_by_col(dim_data_t *d_csr, dim_data_t *d_csc)
{
    if (d_csr->len == 0 || d_csc->len == 0)
        return 0;
    
    int res = 0;
    size_t len_a, len_b;
    dim_data_t data_a, data_b;
    if (d_csr->len <= d_csc->len)
    {
        len_a = d_csr->len;
        len_b = d_csc->len;

        data_a = *d_csr;
        data_b = *d_csc;
    }
    else
    {
        len_a = d_csc->len;
        len_b = d_csr->len;

        data_a = *d_csc;
        data_b = *d_csr;
    }

    size_t j_last = 0;
    for (size_t i = 0; i < len_a; i++)
    {
        for (size_t j = j_last; j < len_b; j++)
        {
            if (data_a.ind[i] == data_b.ind[j])
            {
                res += data_a.value[i] * data_b.value[j];
                j_last = j;
            }
        }
    }

    return res;
}


    // size_t len;
    // if (mtr->type == csr)
    //     len = mtr->m;
    // else of (mtr->type == csc)
    //     len = mtr->n;

    // int rc = create_dim_data(data, len);
    // if (rc != OK)
    //     return rc;
#include <stdio.h>
int mult_csr_by_csc(matrix_t *mtr, matrix_t *m_csr, matrix_t *m_csc)
{
    int rc;
    dim_data_t row, col;
    rc = create_dim_data(&row, m_csr->n);
    if (rc != OK)
        return rc;
    rc = create_dim_data(&col, m_csc->m);
    if (rc != OK)
    {
        free_dim_data(&row);
        return rc;
    }
        

    int val;
    size_t num_count = 0;
    for (size_t i = 0; i < m_csr->n; i++)
    {
        get_dim_data(&row, m_csr, i);
        // for(size_t i = 0; i < row.len; i++)
        //     printf("%d(%u) ", row.value[i], row.ind[i]);
        // printf("\n");


        for (size_t j = 0; j < m_csc->m; j++)
        {
            get_dim_data(&col, m_csc, j);
            // for (size_t i = 0; i < col.len; i++)
            //     printf("%d(%u) ", col.value[i], col.ind[i]);
            // printf("\n");

            val = mult_row_by_col(&row, &col);
            if (val == 0)
                continue;

            mtr->values[num_count] = val;
            mtr->ind[num_count] = j;
            num_count++;
            // break;
        }
        mtr->dim[i] = num_count;
        // break;
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

int classic_mult(matrix_data_t res, matrix_data_t a, matrix_data_t b, size_t n, size_t m, size_t k)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            res[i][j] = 0;
            for (size_t common_i = 0; common_i < m; common_i++)
                res[i][j] += a[i][common_i] * b[common_i][j];
        }
    }

    return OK;
}
