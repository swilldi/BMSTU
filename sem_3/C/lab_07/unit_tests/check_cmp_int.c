#include "check_unit_tests.h"
#include "sort.h"
#include <check.h>

START_TEST(equal_num)
{
    int a = 3, b = 3;
    int res = cmp_int(&a, &b);
    ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_num)
{
    int a = 10, b = 3;
    int res = cmp_int(&a, &b);
    ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(less_num)
{
    int a = 3, b = 10;
    int res = cmp_int(&a, &b);
    ck_assert_int_eq(res, 0);
}
END_TEST

TCase *int_cmp_tcase(void)
{
    TCase *tc = tcase_create("cmp_int");

    tcase_add_test(tc, equal_num);
    tcase_add_test(tc, greater_num);
    tcase_add_test(tc, less_num);

    return tc;
}
