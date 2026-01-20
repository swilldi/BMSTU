#include <check.h>
#include "arr.h"

START_TEST(all_not_even_nums)
{
    int in_arr[] = { 1, 3, 5, 7, 9 };
    int in_len = sizeof(in_arr) / sizeof(int);
    int out_arr[] = { 1, 3, 5, 7, 9 };
    
    int arr[5];
    int len = sizeof(arr) / sizeof(arr[0]);
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(all_even_nums)
{
    int in_arr[] = { 2, 4, 6, 8, 10 };
    int in_len = sizeof(in_arr) / sizeof(int);
    int out_arr[] = { 2, 10, 4, 10, 6, 10, 8, 10, 10, 10 };
    
    int arr[10];
    int len = sizeof(arr) / sizeof(arr[0]);
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(any_even_nums)
{
    int in_arr[] = { 1, 2, 5, 6, 9 };
    int in_len = sizeof(in_arr) / sizeof(in_arr[0]);
    int out_arr[] = { 1, 2, 10, 5, 6, 10, 9 };
    
    int arr[7];
    int len = sizeof(out_arr) / sizeof(out_arr[0]);
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(begin_even)
{
    int in_arr[] = { 2, 3, 5, 7, 9 };
    int in_len = sizeof(in_arr) / sizeof(in_arr[0]);
    int out_arr[] = { 2, 10, 3, 5, 7, 9 };
    
    int arr[6];
    int len = sizeof(out_arr) / sizeof(out_arr[0]);
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(end_even)
{
    int in_arr[] = { 1, 3, 5, 7, 2 };
    int in_len = sizeof(in_arr) / sizeof(in_arr[0]);
    int out_arr[] = { 1, 3, 5, 7, 2, 10 };
    
    int arr[6];
    int len = sizeof(out_arr) / sizeof(out_arr[0]);
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(dublicate_even)
{
    int in_arr[] = { 1, 2, 6, 2, 9 };
    int in_len = sizeof(in_arr) / sizeof(in_arr[0]);
    int out_arr[] = { 1, 2, 10, 6, 10, 2, 10, 9 };
    
    int arr[8];
    int len = sizeof(out_arr) / sizeof(out_arr[0]);
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, OK);

    for (int i = 0; i < len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(small_out_arr)
{
    int in_arr[] = { 4, 2, 5, 7, 9 };
    int in_len = sizeof(in_arr) / sizeof(in_arr[0]);
    
    int arr[5];
    int len = 5;
    int fill_num = 10;

    int rc = arr_add_after_even(in_arr, in_len, arr, &len, fill_num);
    ck_assert_int_eq(rc, ARR_SMALL_SIZE_ERR);

}
END_TEST

TCase *add_after_even_tcase(void)
{
    TCase *tc = tcase_create("key");

    tcase_add_test(tc, all_not_even_nums);
    tcase_add_test(tc, all_even_nums);
    tcase_add_test(tc, any_even_nums);
    tcase_add_test(tc, begin_even);
    tcase_add_test(tc, end_even);
    tcase_add_test(tc, dublicate_even);
    tcase_add_test(tc, small_out_arr);


    return tc;
}
