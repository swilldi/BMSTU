#include "check_unit_tests.h"
#include "sort.h"
#include <check.h>
#include <stdbool.h>

START_TEST(sort_elems)
{
    int arr_in[] = {1, 2, 3, 4, 5}, arr_out[] = {1, 2, 3, 4, 5};

    mysort(arr_in, 5, sizeof(int), cmp_int);

    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(reverse_sort_elem)
{
    int arr_in[5] = {5, 4, 3, 2, 1}, arr_out[5] = {1, 2, 3, 4, 5};

    mysort(arr_in, 5, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(dublicate_elem)
{
    int arr_in[5] = {6, 2, 8, 2, 4}, arr_out[5] = {2, 2, 4, 6, 8};

    mysort(arr_in, 5, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(negative_elem)
{
    int arr_in[5] = {1, 2, 3, -4, 5}, arr_out[5] = {-4, 1, 2, 3, 5};

    mysort(arr_in, 5, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(zero_elem)
{
    int arr_in[5] = {1, 0, 3, 4, -5}, arr_out[5] = {-5, 0, 1, 3, 4};

    mysort(arr_in, 5, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(different_elem_and_position)
{
    int arr_in[5] = {7, 324, 8, -3, 1}, arr_out[5] = {-3, 1, 7, 8, 324};

    mysort(arr_in, 5, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(one_elem)
{
    int arr_in[1] = {1}, arr_out[1] = {1};

    mysort(arr_in, 1, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(two_sort_elem)
{
    int arr_in[2] = {1, 2}, arr_out[2] = {1, 2};

    mysort(arr_in, 2, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

START_TEST(two_not_sort_elem)
{
    int arr_in[2] = {2, 1}, arr_out[2] = {1, 2};

    mysort(arr_in, 2, sizeof(int), cmp_int);
    for (size_t i = 0; i < sizeof(arr_in) / sizeof(int); i++)
        ck_assert_int_eq(arr_out[i], arr_in[i]);
}
END_TEST

#include <stdio.h>
START_TEST(double_sort)
{
    double arr_in[] = { 0.23, 55, 23, -12, 0, 2};
    double arr_out[] = { -12, 0, 0.23, 2, 23, 55};
    const double exp = 1e-3;

    mysort(arr_in, sizeof(arr_in) / sizeof(double), sizeof(double), cmp_double);
    for (size_t i = 0; i < 5; i++)
        ck_assert_double_le(fabs(fabs(arr_out[i]) - fabs(arr_in[i])), exp);
        
}
END_TEST

// START_TEST(double_sort)
// {
//     double arr_in[] = { "d", "c", "a", "b" };
//     double arr_out[] = { "a", "b", "c", "d" };
//     const double exp = 1e-3;

//     mysort(arr_in, 4 , sizeof(char*), cmp_str);
//     for (size_t i = 0; i < 4; i++)
//         ck_assert_double_le(fabs(fabs(arr_out[i]) - fabs(arr_in[i])), exp);
//         ck_assert_str_eq(arr_out[i])
        
// }
// END_TEST

TCase *sort_tcase(void)
{
    TCase *tc = tcase_create("sort");

    tcase_add_test(tc, sort_elems);
    tcase_add_test(tc, reverse_sort_elem);
    tcase_add_test(tc, dublicate_elem);
    tcase_add_test(tc, negative_elem);
    tcase_add_test(tc, zero_elem);
    tcase_add_test(tc, different_elem_and_position);
    tcase_add_test(tc, one_elem);
    tcase_add_test(tc, two_sort_elem);
    tcase_add_test(tc, two_not_sort_elem);
    tcase_add_test(tc, double_sort);


    return tc;
}
