#include <check.h>
#include "arr.h"

START_TEST(len_1)
{
    int out_arr[] = { 2 };
    int fill_len = 1;
    
    int arr[5];
    // int len = sizeof(arr) / sizeof(arr[0]);

    arr_fill_prime_num(arr, fill_len);

    for (int i = 0; i < fill_len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

START_TEST(len_10)
{
    int out_arr[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    int fill_len = 10;
    
    int arr[10];
    // int len = sizeof(arr) / sizeof(arr[0]);

    arr_fill_prime_num(arr, fill_len);

    for (int i = 0; i < fill_len; i++)
        ck_assert_int_eq(arr[i], out_arr[i]);
}
END_TEST

TCase *fill_prime_num_tcase(void)
{
    TCase *tc = tcase_create("arr_fill_prime_num");

    tcase_add_test(tc, len_1);
    tcase_add_test(tc, len_10);

    return tc;
}
