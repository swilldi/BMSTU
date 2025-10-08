#include "check_unit_tests.h"
#include "matrix_func.h"
#include "dynamic_matrix.h"

START_TEST(transpose_1x1)
{
    matrix_t in = create_matrix(1, 1);
    in[0][0] = 1;
    int out[1][1] = { { 1 } };
    matrix_t res = transpose_matrix(in, 1, 1);
    ck_assert_int_eq(res[0][0], out[0][0]);
}
END_TEST

START_TEST(transpose_1xN)
{
    matrix_t in = create_matrix(1, 3);
    in[0][0] = 1;
    in[0][1] = 2;
    in[0][2] = 3;

    int out[3][1] = { {1}, {2}, {3} };
    matrix_t res = transpose_matrix(in, 1, 3);
    for (size_t i = 0; i < 3; i++)
        ck_assert_int_eq(res[i][0], out[i][0]);
    
}
END_TEST

START_TEST(transpose_Nx1)
{
    matrix_t in = create_matrix(3, 1);
    in[0][0] = 1;
    in[1][0] = 2;
    in[2][0] = 3;

    int out[1][3] = { {1, 2, 3} };
    matrix_t res = transpose_matrix(in, 3, 1);
    for (size_t i = 0; i < 3; i++)
        ck_assert_int_eq(res[0][i], out[0][i]);
    
}
END_TEST

START_TEST(transpose_NxM)
{
    size_t n = 3, m = 4;
    int tmp[3][4] = {
        { 1, 2, 3, 4}, 
        { 2, 3, 4, 5}, 
        { 3, 4, 5, 6 }
    };
    matrix_t in = create_matrix(n, m);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            in[i][j] = tmp[i][j];

    int out[4][3] = {
        {1, 2, 3}, 
        {2, 3, 4}, 
        {3, 4, 5}, 
        {4, 5, 6}
    };

    matrix_t res = transpose_matrix(in, n, m);
    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < n; j++)
            ck_assert_int_eq(res[i][j], out[i][j]);
}
END_TEST

START_TEST(mult_sqr_matr)
{
    int tmp_a[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6},
        {1, 3, 5}
    };
    int tmp_b[3][3] = {
        {5, 0, 1},
        {7, 6, 1},
        {0, 4, 1}
    };
    int out[3][3] = {
        { 19, 24, 6 },
        { 55, 54, 15 },
        { 26, 38, 9 }
    };

    matrix_t a = create_matrix(3, 3);
    matrix_t b = create_matrix(3, 3);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            a[i][j] = tmp_a[i][j];
            b[i][j] = tmp_b[i][j];
        }
    }
        

    matrix_t res = mult_sqr_matrix(a, b, 3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(res[i][j], out[i][j]);
        
    free(res);
    free(a);
    free(b);

}
END_TEST

START_TEST(mult_a_by_singular)
{
    int tmp_a[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6},
        {1, 3, 5}
    };
    int tmp_b[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    int out[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6},
        {1, 3, 5}
    };

    matrix_t a = create_matrix(3, 3);
    matrix_t b = create_matrix(3, 3);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            a[i][j] = tmp_a[i][j];
            b[i][j] = tmp_b[i][j];
        }
    }
        

    matrix_t res = mult_sqr_matrix(a, b, 3);
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_int_eq(res[i][j], out[i][j]);
        
    free(res);
    free(a);
    free(b);

}
END_TEST

TCase* create_tests_matrix_func(void)
{
    TCase* tc = tcase_create("matrix func") ;
    tcase_add_test(tc, transpose_1x1);
    tcase_add_test(tc, transpose_1xN);
    tcase_add_test(tc, transpose_Nx1);
    tcase_add_test(tc, transpose_NxM);
    tcase_add_test(tc, mult_sqr_matr);
    tcase_add_test(tc, mult_a_by_singular);
    
    return tc;
}
