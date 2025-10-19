#include "input_func.h"
#include "dynamic_mem.h"
#include "matrix_struct.h"
#include "exit_code.h"
#include "matrix_func.h"
#include "enums.h"
#include "time.h"

#define TEST_COUNT 3
#define PRE_TEST_COUNT 5

size_t amount_no_zero(matrix_data_t mtr, size_t n, size_t m)
{
    size_t amount = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (mtr[i][j])
                amount++;
        }
    }

    return amount;
}

int get_matrix_info(char *file_name, double *k_razr_1, size_t *max_elem_1, double *k_razr_2, size_t *max_elem_2)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_FILE_ERR;

    int rc;
    size_m n = 0, m, p = 0, q;
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    
    // ввод матриц
    rc = input_matrix(&m_1, &n, &m, f, input_matrix_coord);
    if (rc != OK)
        return rc;
    
    // print_matrix(m_1, n, m);
    
    rc = input_matrix(&m_2, &p, &q, f, input_matrix_coord);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        return rc;
    }

    fclose(f);

    *max_elem_1 = n * m;
    *max_elem_2 = p * q;

    *k_razr_1 = (double)amount_no_zero(m_1, n, m) / (n * m);
    *k_razr_2 = (double)amount_no_zero(m_2, p, q) / (p * q);

    return OK;
}

int test_compress(char *file_name, double *time_res, size_t *memory_res)
{
    *time_res = 0;
    *memory_res = 0;

    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_FILE_ERR;

    int rc;
    size_m n = 0, m, p = 0, q;
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    matrix_t m_csr = { 0 }, m_csc = { 0 }, res = { 0 };

    clock_t start, end;
    
    // ввод матриц
    rc = input_matrix(&m_1, &n, &m, f, input_matrix_coord);
    if (rc != OK)
        return rc;
    
    // print_matrix(m_1, n, m);
    
    rc = input_matrix(&m_2, &p, &q, f, input_matrix_coord);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        return rc;
    }

    fclose(f);

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        // преобразование матриц к сжатому виду
        rc = matrix_to_csr(&m_csr, m_1, n, m);
        if (rc != OK)
        {
            if (i)
            {
                free_matrix_razr(&res);
                free_matrix_razr(&m_csc);
                free_matrix_razr(&m_csr);
            }
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }

        rc = matrix_to_csc(&m_csc, m_2, p, q);
        if (rc != OK)
        {
            if (i)
            {
                free_matrix_razr(&res);
                free_matrix_razr(&m_csc);
            }
            free_matrix_razr(&m_csr);
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }

        // умножение матриц
        rc = mult_csr_by_csc(&res, &m_csr, &m_csc);
        if (rc != OK)
        {
            if (i)
                free_matrix_razr(&res);
            free_matrix_razr(&m_csr);
            free_matrix_razr(&m_csc);
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }
        free_matrix_razr(&res);
    }

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        start =clock();
        // преобразование матриц к сжатому виду
        rc = matrix_to_csr(&m_csr, m_1, n, m);
        if (rc != OK)
        {
            if (i)
            {
                free_matrix_razr(&res);
                free_matrix_razr(&m_csc);
                free_matrix_razr(&m_csr);
            }
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }

        rc = matrix_to_csc(&m_csc, m_2, p, q);
        if (rc != OK)
        {
            if (i)
            {
                free_matrix_razr(&res);
                free_matrix_razr(&m_csc);
            }
            free_matrix_razr(&m_csr);
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }

        // умножение матриц
        rc = mult_csr_by_csc(&res, &m_csr, &m_csc);
        if (rc != OK)
        {
            if (i)
                free_matrix_razr(&res);
            free_matrix_razr(&m_csr);
            free_matrix_razr(&m_csc);
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }
        end = clock();

        *time_res += end - start;
        free_matrix_razr(&res);
    }
    
    *time_res /= TEST_COUNT;
    *memory_res = (n + m + 2 * m_csc.max_values + 2 * m_csr.max_values) * sizeof(int);

    
    free_matrix_razr(&m_csr);
    free_matrix_razr(&m_csc);
    free_matrix(&m_1, n);
    free_matrix(&m_2, p);
    
    return OK;
}

int test_classic(char *file_name, double *time_res, size_t *memory_res)
{
    *time_res = 0;
    *memory_res = 0;
    
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_FILE_ERR;

    int rc;
    size_m n = 0, m, p = 0, q;
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    matrix_data_t res = NULL;

    clock_t start, end;
    
    // ввод матриц
    rc = input_matrix(&m_1, &n, &m, f, input_matrix_coord);
    if (rc != OK)
        return rc;
    
    // print_matrix(m_1, n, m);
    
    rc = input_matrix(&m_2, &p, &q, f, input_matrix_coord);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        return rc;
    }

    fclose(f);

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        // умножение матриц
        rc = classic_mult(&res, m_1, m_2, n, m, q);
        if (rc != OK)
        {
            if (i)
                free_matrix(&res, n);
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }
        free_matrix(&res, n);
    }

    for (size_t i = 0; i < TEST_COUNT; i++)
    {

        start =clock();
        // умножение матриц
        rc = classic_mult(&res, m_1, m_2, n, m, q);
        if (rc != OK)
        {
            if (i)
                free_matrix(&res, n);
            free_matrix(&m_1, n);
            free_matrix(&m_2, p);
            return rc;
        }
        end = clock();
        
        *time_res += end - start;
        free_matrix(&res, n);
    }

    *time_res /= TEST_COUNT;
    *memory_res = (n * m + p * q + n * q) * sizeof(int);

    free_matrix(&res, n);
    free_matrix(&m_1, n);
    free_matrix(&m_2, p);
    return OK;
}


int start_testa(void)
{
    char *paths[] = 
    {
        "./test_files/test_matrix_5x5_1.txt",
        "./test_files/test_matrix_5x5_2.txt",
        "./test_files/test_matrix_5x5_3.txt",
        "./test_files/test_matrix_5x5_4.txt",
        "./test_files/test_matrix_5x5_5.txt",

        "./test_files/test_matrix_5x10_1.txt",
        "./test_files/test_matrix_5x10_2.txt",
        "./test_files/test_matrix_5x10_3.txt",
        "./test_files/test_matrix_5x10_4.txt",
        "./test_files/test_matrix_5x10_5.txt",

        "./test_files/test_matrix_10x10_1.txt",
        "./test_files/test_matrix_10x10_2.txt",
        "./test_files/test_matrix_10x10_3.txt",
        "./test_files/test_matrix_10x10_4.txt",
        "./test_files/test_matrix_10x10_5.txt",

        "./test_files/test_matrix_20x20_1.txt",
        "./test_files/test_matrix_20x20_2.txt",
        "./test_files/test_matrix_20x20_3.txt",
        "./test_files/test_matrix_20x20_4.txt",
        "./test_files/test_matrix_20x20_5.txt",

        "./test_files/test_matrix_20x50_1.txt",
        "./test_files/test_matrix_20x50_2.txt",
        "./test_files/test_matrix_20x50_3.txt",
        "./test_files/test_matrix_20x50_4.txt",
        "./test_files/test_matrix_20x50_5.txt",

        "./test_files/test_matrix_100x20_1.txt",
        "./test_files/test_matrix_100x20_2.txt",
        "./test_files/test_matrix_100x20_3.txt",
        "./test_files/test_matrix_100x20_4.txt",
        "./test_files/test_matrix_100x20_5.txt",

        "./test_files/test_matrix_100x30_1.txt",
        "./test_files/test_matrix_100x30_2.txt",
        "./test_files/test_matrix_100x30_3.txt",
        "./test_files/test_matrix_100x30_4.txt",
        "./test_files/test_matrix_100x30_5.txt",

        "./test_files/test_matrix_100x40_1.txt",
        "./test_files/test_matrix_100x40_2.txt",
        "./test_files/test_matrix_100x40_3.txt",
        "./test_files/test_matrix_100x40_4.txt",
        "./test_files/test_matrix_100x40_5.txt",

        "./test_files/test_matrix_100x50_1.txt",
        "./test_files/test_matrix_100x50_2.txt",
        "./test_files/test_matrix_100x50_3.txt",
        "./test_files/test_matrix_100x50_4.txt",
        "./test_files/test_matrix_100x50_5.txt",

        "./test_files/test_matrix_100x100_1.txt",
        "./test_files/test_matrix_100x100_2.txt",
        "./test_files/test_matrix_100x100_3.txt",
        "./test_files/test_matrix_100x100_4.txt",
        "./test_files/test_matrix_100x100_5.txt",

        "./test_files/test_matrix_500x1000_1.txt",
        "./test_files/test_matrix_500x1000_2.txt",
        "./test_files/test_matrix_500x1000_3.txt",
        "./test_files/test_matrix_500x1000_4.txt",
        "./test_files/test_matrix_500x1000_5.txt"
    };

    int rc;
    double time_res_compr, time_res_classic;
    size_t memory_res_compr, memory_res_classic;
    double k_razr_1, k_razr_2;
    size_t amount_elem_1, amount_elem_2;


    printf(
        "|----------------------------------------------------------------------------------------------------------------------------|||-----------------------|\n"
        "|                   CSR/CSC                                   ||                                     CLASSIC                 |||        Сравнение      |\n"
        "|----------------------------------------------------------------------------------------------------------------------------|||-----------------------|\n"
        "| кол-во элем. | заполненость, %% | время, сек | Память, байт  || кол-во элем. | заполненость, %% | время, сек | Память, байт  |||  Время, %% | Память, %% |\n"
        "|----------------------------------------------------------------------------------------------------------------------------|||-----------------------|\n"
    );
            

    for (size_t i = 0; i < sizeof(paths) / sizeof(*paths); i++)
    {
        rc = test_compress(paths[i], &time_res_compr, &memory_res_compr);
        if (rc != OK)
            return rc;
        rc = test_classic(paths[i], &time_res_classic, &memory_res_classic);
        if (rc != OK)
            return rc;
        
        rc = get_matrix_info(paths[i], &k_razr_1, &amount_elem_1, &k_razr_2, &amount_elem_2);
        
        time_res_classic /= CLOCKS_PER_SEC;
        time_res_compr /= CLOCKS_PER_SEC;
        
        printf("| %12ld | %15.2lf | %10lf | %12ld  || %12ld | %15.2lf | %10lf | %12ld  ||| %9.2lf | %9.2lf |\n", 
                amount_elem_1, k_razr_1 * 100, time_res_compr, memory_res_compr, 
                amount_elem_2, k_razr_2 * 100, time_res_classic, memory_res_classic,
                (time_res_classic - time_res_compr) / time_res_classic * 100,
                ((double)memory_res_classic - memory_res_compr) / (double)memory_res_classic * 100
        );

        if ((i + 1) % 5 == 0)
            printf("|----------------------------------------------------------------------------------------------------------------------------|||-----------------------|\n");
    }
    
    return OK;
}

