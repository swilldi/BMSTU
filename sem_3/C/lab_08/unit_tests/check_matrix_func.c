#include "check_unit_tests.h"
#include "matrix_func.h"
#include "dynamic_matrix.h"
#include <check.h>
#include <stdbool.h>


// проверка сложения матрицы
START_TEST(check_sum_matrix)
{
    double **mtr_1, **mtr_2, **res;
    mtr_1 = create_matrix(3, 3);
    mtr_2 = create_matrix(3, 3);
    double mtr_out[3][3] =
    {
        {1, 2, 0},
        {1, 2, 1},
        {0, 13, 0}
    };

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            mtr_1[i][j] = 0;
            mtr_2[i][j] = 0;
        }
    } 

    mtr_1[0][0] = 1;
    mtr_1[1][0] = 1;
    mtr_1[1][2] = 1;
    mtr_1[2][1] = 10;

    mtr_2[0][1] = 2;
    mtr_2[1][1] = 2;
    mtr_2[2][1] = 3;

    sum_matrix(&res, mtr_1, mtr_2, 3, 3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);
        
    free_matrix(mtr_1);
    free_matrix(mtr_2);
    free_matrix(res);
}
END_TEST

// проверка сложения матрицы с нулевой матрицей
START_TEST(sum_with_zero_matrix)
{
    double **mtr_1, **mtr_2, **res;
    mtr_1 = create_matrix(3, 3);
    mtr_2 = create_matrix(3, 3);
    double mtr_out[3][3] =
    {
        {1, 0, 0},
        {1, 0, 1},
        {0, 10, 0}
    };

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            mtr_1[i][j] = 0;
            mtr_2[i][j] = 0;
        }
    } 

    mtr_1[0][0] = 1;
    mtr_1[1][0] = 1;
    mtr_1[1][2] = 1;
    mtr_1[2][1] = 10;

    sum_matrix(&res, mtr_1, mtr_2, 3, 3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);
    
    free_matrix(mtr_1);
    free_matrix(mtr_2);
    free_matrix(res);
}
END_TEST

// проверка умножения матриц
START_TEST(check_mult_matrix)
{
    double **mtr_1, **mtr_2, **res;
    mtr_1 = create_matrix(3, 3);
    mtr_2 = create_matrix(3, 3);
    double mtr_out[3][3] =
    {
        {0, 2, 0},
        {0, 5, 0},
        {0, 20, 0}
    };

        for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            mtr_1[i][j] = 0;
            mtr_2[i][j] = 0;
        }
    }

    mtr_1[0][0] = 1;
    mtr_1[1][0] = 1;
    mtr_1[1][2] = 1;
    mtr_1[2][1] = 10;

    mtr_2[0][1] = 2;
    mtr_2[1][1] = 2;
    mtr_2[2][1] = 3;

    mult_matrix(&res, mtr_1, mtr_2, 3, 3, 3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);
    
    free_matrix(mtr_1);
    free_matrix(mtr_2);
    free_matrix(res);
}
END_TEST

// провека умножения на матрицу столбец
START_TEST(mult_col_matrix)
{
    double **mtr_1, **mtr_2, **res;
    mtr_1 = create_matrix(3, 3);
    mtr_2 = create_matrix(3, 1);
    double mtr_out[3][1] =
    {
        { 1 },
        { 4 },
        { 20 }
    };

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            mtr_1[i][j] = 0;
            if (j == 0)
                mtr_2[i][j] = 0;
        }
    }

    mtr_1[0][0] = 1;
    mtr_1[1][0] = 1;
    mtr_1[1][2] = 1;
    mtr_1[2][1] = 10;

    mtr_2[0][0] = 1;
    mtr_2[1][0] = 2;
    mtr_2[2][0] = 3;

    mult_matrix(&res, mtr_1, mtr_2, 3, 3, 1);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 1; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);

    free_matrix(mtr_1);
    free_matrix(mtr_2);
    free_matrix(res);
}
END_TEST

// Умножение на единичную матрицу
START_TEST(mult_E_matrix)
{
    double **mtr_1, **mtr_2, **res;
    mtr_1 = create_matrix(3, 3);
    mtr_2 = create_matrix(3, 3);
    double mtr_out[3][3] =
    {
        {1, 0, 0},
        {1, 0, 1},
        {0, 10, 0}
    };

        for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            mtr_1[i][j] = 0;
            mtr_2[i][j] = 0;
        }
    }

    mtr_1[0][0] = 1;
    mtr_1[1][0] = 1;
    mtr_1[1][2] = 1;
    mtr_1[2][1] = 10;

    mtr_2[0][0] = 1;
    mtr_2[1][1] = 1;
    mtr_2[2][2] = 1;

    mult_matrix(&res, mtr_1, mtr_2, 3, 3, 3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);

    free_matrix(mtr_1);
    free_matrix(mtr_2);
    free_matrix(res);
}
END_TEST

// умножение не квадратных матриц
START_TEST(mult_no_sqr_matrix)
{
    double **mtr_1, **mtr_2, **res;
    mtr_1 = create_matrix(2, 3);
    mtr_2 = create_matrix(3, 4);
    double mtr_out[2][4] =
    {
        {1, 0, 6, 0},
        {4, 0, 6, 0},
    };

        for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if (j < 3 && i < 2)
                mtr_1[i][j] = 0;

            mtr_2[i][j] = 0;
        }
    }

    mtr_1[0][0] = 1;
    mtr_1[1][0] = 1;
    mtr_1[1][2] = 1;

    mtr_2[0][0] = 1;
    mtr_2[1][0] = 2;
    mtr_2[2][0] = 3;
    mtr_2[0][2] = 6;
    mtr_2[1][3] = 5;

    mult_matrix(&res, mtr_1, mtr_2, 2, 3, 4);

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 4; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);
    
    free_matrix(mtr_1);
    free_matrix(mtr_2);
    free_matrix(res);
}
END_TEST

// проверка поиска обратной матрицы
START_TEST(check_rev_mtr)
{
    matrix_t mtr = create_matrix(3, 3);
    matrix_t res;
    
    mtr[0][0] = 1;
    mtr[0][1] = 1;
    mtr[0][2] = 1;
    
    mtr[1][0] = 3;
    mtr[1][1] = 2;
    mtr[1][2] = 2;

    mtr[2][0] = 2;
    mtr[2][1] = 2;
    mtr[2][2] = 3;

    double mtr_out[3][3] = {
        { -2, 1, 0 },
        { 5, -1, -1 },
        { -2, 0, 1 }
    };

    inverse_matrix(&res, mtr, 3);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            ck_assert_double_le(fabs(res[i][j] - mtr_out[i][j]), EPS);

    free_matrix(mtr);
    free_matrix(res);
}
END_TEST

// обратную матрицу получить невозможно
START_TEST(not_rev_mtr)
{
    matrix_t mtr = create_matrix(3, 3);
    ck_assert(mtr);
    matrix_t res;
    
    mtr[0][0] = 1;
    mtr[0][1] = 1;
    mtr[0][2] = 1;
    
    mtr[1][0] = 1;
    mtr[1][1] = 1;
    mtr[1][2] = 1;

    mtr[2][0] = 1;
    mtr[2][1] = 1;
    mtr[2][2] = 1;

    int rc = inverse_matrix(&res, mtr, 3);
    ck_assert(rc == ZERO_MATRIX);
    
    free_matrix(mtr);
}
END_TEST

TCase *matrix_func_tcase(void)
{
    TCase *tc = tcase_create("matrix_func");

    tcase_add_test(tc, check_sum_matrix);
    tcase_add_test(tc, sum_with_zero_matrix);
    tcase_add_test(tc, check_mult_matrix);
    tcase_add_test(tc, mult_col_matrix);
    tcase_add_test(tc, mult_col_matrix);    
    tcase_add_test(tc, mult_E_matrix);
    tcase_add_test(tc, mult_no_sqr_matrix);
    tcase_add_test(tc, check_rev_mtr);
    tcase_add_test(tc, not_rev_mtr);

    return tc;
}
