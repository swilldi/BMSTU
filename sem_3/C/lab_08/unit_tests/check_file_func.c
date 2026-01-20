#include "check_unit_tests.h"
#include <check.h>
#include "dynamic_matrix.h"

#include "file_func.h"

// Считывание матрицы из файла
START_TEST(read_matrix_from_file)
{
    int rc;
    size_t n, m;
    double **mtr = NULL, out_mtr[3][3] = { {1, 2, 3}, {1, 2, 3}, {1, 2, 3} };
    FILE *f = fopen("./unit_tests/files/read_mtr_from_file.txt", "r");
    ck_assert(f);
    rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == OK);

    mtr = create_matrix(n, m);
    ck_assert(mtr);

    rc = read_matrix(f, mtr, n, m);
    ck_assert(rc == OK);

    fclose(f);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        ck_assert_double_le(fabs(mtr[i][j] - out_mtr[i][j]), EPS);
    
    free_matrix(mtr);
    
}
END_TEST

// Элементов в матрице меньше, чем размер
START_TEST(few_elem_in_file)
{
    int rc;
    size_t n, m;
    double **mtr = NULL;
    FILE *f = fopen("./unit_tests/files/few_elem_in_file.txt", "r");
    ck_assert(f);
    rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == OK);
    
    mtr = create_matrix(n, m);
    ck_assert(mtr);

    rc = read_matrix(f, mtr, n, m);
    ck_assert(rc == IO_ERR);

    free_matrix(mtr);
}
END_TEST

// Отрицательный размер матрицы
START_TEST(negative_size)
{
    int rc;
    size_t n, m;
    FILE *f = fopen("./unit_tests/files/negative_size.txt", "r");
    ck_assert(f);
    rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == RANGE_ERR);
}
END_TEST

// Размер матрицы – не число
START_TEST(not_num_size)
{
    int rc;
    size_t n, m;
    FILE *f = fopen("./unit_tests/files/not_num_size.txt", "r");
    ck_assert(f);
    rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == IO_ERR);
}
END_TEST

// Элемент матрицы не число
START_TEST(elem_not_num)
{
    int rc;
    size_t n, m;
    double **mtr = NULL;
    FILE *f = fopen("./unit_tests/files/elem_not_num.txt", "r");
    ck_assert(f);
    rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == OK);    
    
    mtr = create_matrix(n, m);
    ck_assert(mtr);

    rc = read_matrix(f, mtr, n, m);
    ck_assert(rc == IO_ERR);

    free_matrix(mtr);
}
END_TEST

// Запись матрицы в файл
START_TEST(write_matrix_to_file)
{
    int rc; 
    size_t n, m;
    double **mtr = NULL, **out_mtr_d = NULL, out_mtr[3][3] = { {1, 2, 3}, {1, 2, 3}, {1, 2, 3} };
    
    out_mtr_d = create_matrix(3, 3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            out_mtr_d[i][j] = out_mtr[i][j];

    FILE *f = fopen("./unit_tests/files/tmp.txt", "w");
    write_matrix(f, out_mtr_d, 3, 3);
    fclose(f);

    f = fopen("./unit_tests/files/tmp.txt", "r");
    rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == OK);
    mtr = create_matrix(n, m);
    ck_assert(mtr);
    rc = read_matrix(f, mtr, 3, 3);
    ck_assert(rc == OK);
    fclose(f);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_double_le(fabs(mtr[i][j] - out_mtr[i][j]), EPS);
    
    free_matrix(mtr);
    free_matrix(out_mtr_d);
    
}
END_TEST

// Проверка файла на пустоту
START_TEST(check_file_is_empty)
{
    FILE *f = fopen("./unit_tests/files/empty_file.txt", "r");
    ck_assert(check_file(f) == FILE_EMPTY_ERR);
    fclose(f);
}
END_TEST

// Проверка файл не пустой
START_TEST(check_file_is_not_empty)
{
    FILE *f = fopen("./unit_tests/files/read_mtr_from_file.txt", "r");
    ck_assert(check_file(f) == OK);
    fclose(f);
}
END_TEST

// проверка чтения размеров матрицы из файла
START_TEST(check_matrix_size_from_file)
{
    FILE *f = fopen("./unit_tests/files/matrix_size_from_file.txt", "r");
    size_t n, m;
    int rc = read_matrix_sizes(f, &n, &m);
    ck_assert(rc == OK);
    ck_assert_uint_eq(n, 3);
    ck_assert_uint_eq(m, 3);
    fclose(f);
}
END_TEST

TCase *file_func_tcase(void)
{




    TCase *tc = tcase_create("file_func");
    tcase_add_test(tc, read_matrix_from_file);
    tcase_add_test(tc, write_matrix_to_file);
    tcase_add_test(tc, check_file_is_empty);
    tcase_add_test(tc, check_matrix_size_from_file);
    tcase_add_test(tc, few_elem_in_file);
    tcase_add_test(tc, negative_size);
    tcase_add_test(tc, not_num_size);
    tcase_add_test(tc, elem_not_num);
    tcase_add_test(tc, check_file_is_not_empty);

    return tc;
}
