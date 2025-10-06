#include "arr_func.h"
#include "check_unit_tests.h"
#include "exit_code.h"
#include <check.h>

START_TEST(all_negative)
{
    int arr[] = {-1, -2, -3, -4}, *arr_f_b = NULL, *arr_f_e;
    size_t len = 4;
    key(arr, arr + len, &arr_f_b, &arr_f_e);

    int arr_out[] = {-1, -2, -3};
    for (size_t i = 0; i < 3; i++)
        ck_assert_int_eq(arr_f_b[i], arr_out[i]);
    free(arr_f_b);
}
END_TEST

START_TEST(no_negative)
{
    int arr[] = {1, 2, 3, 4}, *arr_f_b = NULL, *arr_f_e;
    size_t len = 4;
    key(arr, arr + len, &arr_f_b, &arr_f_e);

    int arr_out[] = {1, 2, 3, 4};
    for (size_t i = 0; i < len; i++)
        ck_assert_int_eq(arr_f_b[i], arr_out[i]);
    free(arr_f_b);
}
END_TEST

START_TEST(first_negative)
{
    int arr[] = {-1, 2, 3, 4}, *arr_f_b = NULL, *arr_f_e;
    size_t len = 4;
    int rc = key(arr, arr + len, &arr_f_b, &arr_f_e);

    ck_assert_int_eq(rc, EMPTY_ARR);
    free(arr_f_b);
}
END_TEST

START_TEST(last_negative)
{
    int arr[] = {1, 2, 3, -4}, *arr_f_b = NULL, *arr_f_e;
    size_t len = 4;
    key(arr, arr + len, &arr_f_b, &arr_f_e);

    int arr_out[] = {1, 2, 3};
    for (size_t i = 0; i < 3; i++)
        ck_assert_int_eq(arr_f_b[i], arr_out[i]);
    free(arr_f_b);
}
END_TEST

START_TEST(any_negative)
{
    int arr[] = {1, 2, -3, 4, 5, -6, 7, 8, 9}, *arr_f_b = NULL, *arr_f_e;
    size_t len = 9;
    key(arr, arr + len, &arr_f_b, &arr_f_e);

    int arr_out[] = {1, 2, -3, 4, 5};
    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(arr_f_b[i], arr_out[i]);
    free(arr_f_b);
}
END_TEST

TCase *key_tcase(void)
{
    TCase *tc = tcase_create("key");

    tcase_add_test(tc, all_negative);
    tcase_add_test(tc, no_negative);
    tcase_add_test(tc, first_negative);
    tcase_add_test(tc, last_negative);
    tcase_add_test(tc, any_negative);

    return tc;
}
