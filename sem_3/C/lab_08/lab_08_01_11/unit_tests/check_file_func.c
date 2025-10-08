#include "check_unit_tests.h"
#include <check.h>

#include "file_func.h"

START_TEST(read_array_from_file)
{
    int nums[4], out_nums[] = {1, 2, 3, 4};
    FILE *f = fopen("./unit_tests/files/read_arr_from_file.txt", "r");
    read_array(f, nums, nums + 4);
    for (size_t i = 0; i < 4; i++)
        ck_assert_int_eq(nums[i], out_nums[i]);
    fclose(f);
}
END_TEST

START_TEST(write_array_to_file)
{
    int arr[] = {1, 2, 3, 4};
    FILE *f = fopen("./unit_tests/files/tmp.txt", "w");
    write_array(f, arr, arr + 4);
    fclose(f);

    int arr_out[4];
    f = fopen("./unit_tests/files/tmp.txt", "r");
    read_array(f, arr_out, arr_out + 4);
    fclose(f);

    for (size_t i = 0; i < 4; i++)
        ck_assert_int_eq(arr[i], arr_out[i]);
}
END_TEST

START_TEST(check_file_is_empty)
{
    FILE *f = fopen("./unit_tests/files/empty_file.txt", "r");
    ck_assert(file_is_empty(f));
    fclose(f);
}
END_TEST

START_TEST(count_nums_in_file)
{
    FILE *f = fopen("./unit_tests/files/count_nums_in_file.txt", "r");
    size_t c;
    count_nums(f, &c);
    ck_assert_uint_eq(c, 7);
    fclose(f);
}
END_TEST

TCase *file_func_tcase(void)
{
    TCase *tc = tcase_create("file_func");
    tcase_add_test(tc, read_array_from_file);
    tcase_add_test(tc, write_array_to_file);
    tcase_add_test(tc, check_file_is_empty);
    tcase_add_test(tc, count_nums_in_file);

    return tc;
}
