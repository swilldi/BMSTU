#include "test.h"
#include "input_func.h"
#include "output_func.h"
#include "dynamic_mem.h"
#include "matrix_struct.h"
#include "exit_code.h"
#include "matrix_func.h"
#include "enums.h"

#define PRE_TEST_COUNT 0
#define TEST_COUNT 1

#define ST_HEADER_METHOD "| count | by_table, сек | by_key, сек | by_key / by_table, %% | cars mem, b  | keys mem, b | keys / cars, %% |\n"
#define ST_HEADER_SORT   "| count |  quick, сек   | shaker, сек |   quick / shaker, %%  | cars mem, b  | keys mem, b | keys / cars, %% |\n"
#define ST_SEPARATOR     "--------+---------------+-------------+----------------------+--------------+-------------+-----------------\n"



void test_csr(FILE *f, double *res_time, size_t *res_memory)
{
    fseek(f, 0, SEEK_SET);

    clock_t start, end;
    *res_time = 0;
    *res_memory = 0;
    
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    matrix_t m_csr = { 0 }, m_csc = { 0 }, res = { 0 };
    size_m n, m, p, q;

    input_matrix(&m_1, &n, &m, f, input_matrix_coord);
    input_matrix(&m_2, &p, &q, f, input_matrix_coord);

    int rc = create_matrix_razr(&m_csr, n, m, csr);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        return;
    }
    
    rc = create_matrix_razr(&m_csc, p, q, csc);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        free_matrix_razr(&m_csr);
        return;
    }

    rc = create_matrix_razr(&res, n, q, csr);
    if (rc != OK)
    {
        free_matrix(&m_1, n);
        free_matrix(&m_2, p);
        free_matrix_razr(&m_csr);
        free_matrix_razr(&m_csc);
        return;
    }

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        matrix_to_csr(&m_csr, m_1, n, m);
        matrix_to_csc(&m_csc, m_2, p, q);
        mult_csr_by_csc(&res, &m_csr, &m_csc);
    }
    
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        start = clock();
        matrix_to_csr(&m_csr, m_1, n, m);
        matrix_to_csc(&m_csc, m_2, p, q);
        mult_csr_by_csc(&res, &m_csr, &m_csc);
        end = clock();

        *res_time = (end - start + *res_time) / 2;
    }

                     

    free_matrix(&m_1, n);
    free_matrix(&m_2, p);
    free_matrix_razr(&m_csc);
    free_matrix_razr(&m_csr);
    free_matrix_razr(&res);
    
    *res_time /= CLOCKS_PER_SEC;
}


void test_classic(FILE *f, double *res_time, size_t *res_memory)
{
    fseek(f, 0, SEEK_SET);

    clock_t start, end;
    *res_time = 0;
    *res_memory = 0;
    
    matrix_data_t m_1 = NULL;
    matrix_data_t m_2 = NULL;
    matrix_data_t res = NULL;
    size_m n, m, p, q;

    input_matrix(&m_1, &n, &m, f, input_matrix_coord);
    input_matrix(&m_2, &p, &q, f, input_matrix_coord);
    res = create_matrix(n, q);
    if (!res)
        return;


    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        classic_mult(res, m_1, m_2, n, m, q);
    }
    
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        start = clock();
        classic_mult(res, m_1, m_2, n, m, q);
        end = clock();

        *res_time = (end - start + *res_time) / 2;
    }

    free_matrix(&m_1, n);
    free_matrix(&m_2, p);
    free_matrix(&res, n);

    // *res_memory = sizeof(int) * m + sizeof(int*) * n + sizeof(int) * q + sizeof(int*) * p + sizeof(int) * q + sizeof(int*) * n; 
    *res_time /= CLOCKS_PER_SEC;
}


int test_mult_method(void)
{
    // int rc; 
    char *(paths[]) = {
        "./test_files/test_matrix_5x5_1.txt",
        "./test_files/test_matrix_5x5_2.txt",
        "./test_files/test_matrix_5x5_3.txt",
        "./test_files/test_matrix_5x5_4.txt",
        "./test_files/test_matrix_5x10_1.txt",
        "./test_files/test_matrix_5x10_2.txt",
        "./test_files/test_matrix_5x10_3.txt",
        "./test_files/test_matrix_5x10_4.txt",
        "./test_files/test_matrix_10x10_1.txt",
        "./test_files/test_matrix_10x10_2.txt",
        "./test_files/test_matrix_10x10_3.txt",
        "./test_files/test_matrix_10x10_4.txt",
        "./test_files/test_matrix_20x20_1.txt",
        "./test_files/test_matrix_20x20_2.txt",
        "./test_files/test_matrix_20x20_3.txt",
        "./test_files/test_matrix_20x20_4.txt",
        "./test_files/test_matrix_100x50_1.txt",
        "./test_files/test_matrix_100x50_2.txt",
        "./test_files/test_matrix_100x50_3.txt",
        "./test_files/test_matrix_100x50_4.txt",
        "./test_files/test_matrix_100x100_1.txt",
        "./test_files/test_matrix_100x100_2.txt",
        "./test_files/test_matrix_100x100_3.txt",
        "./test_files/test_matrix_100x100_4.txt",
        "./test_files/test_matrix_1000x1000_1.txt",
        "./test_files/test_matrix_1000x1000_2.txt",
        "./test_files/test_matrix_1000x1000_3.txt",
        "./test_files/test_matrix_1000x1000_4.txt"
    };

    printf(
        // ST_SEPARATOR
        // ST_HEADER_SORT
        ST_SEPARATOR
    );

    for (size_t i = 0; i < sizeof(paths) / sizeof(*paths); i++)
    {
        double csr_time, classic_time;
        size_t csr_mem, classic_mem;
        size_m n, m;
        double k_razr;

        FILE *f = NULL;
        
        f = fopen((char *)paths[i], "r");
        if (f == NULL)
            return 1;

        get_sizes(f, &n, &m);
        get_k_razr(f, &k_razr);

        test_csr(f, &csr_time, &csr_mem);
        test_classic(f, &classic_time, &classic_mem);

        fclose(f);
        
        // size_t cars_mem = sizeof(car_t) * count, keys_mem = sizeof(key_value_t) * count;
        double percent_time = (classic_time - csr_time) / classic_time * 100;
        double percent_memory = (double)(csr_mem - classic_mem) / csr_mem * 100;
        double percent_razr = k_razr * 100;
        
        // printf("| %5lu | %13.5lf | %11.5lf | %19.2lf%% | %12lu | %11lu | %14.2lf |\n", count, res_quick, res_shaker, percent_time, cars_mem, keys_mem, percent_memory);
        printf("| %6u | %4.2lf | %lf | %lf | %lf | %zu | %zu | %lf |\n", n * m, percent_razr, csr_time, classic_time, percent_time, csr_mem, classic_mem, percent_memory);
    }
    printf(ST_SEPARATOR);
    return OK;
}

void get_sizes(FILE *f, size_m *n, size_m *m)
{
    fseek(f, 0, SEEK_SET);
    fscanf(f, "%u%u", n, m);

}

void get_k_razr(FILE *f, double *k_razr)
{
    fseek(f, 0, SEEK_SET);

    char buff[BUFF_LEN];
    size_t count = 0;
    size_m n, m;

    fscanf(f, "%u%u", &n, &m);

    int c;
    while ((c = fgetc(f)) != '\n' && c != EOF);

    while (fgets(buff, sizeof(buff), f))
    {
        if (buff[0] == '\n')
            break;

        count++;
    }

    *k_razr = (double)count / n / m;
}
