#include <check.h>

#include "check_unit_tests.h"
#include "cmp_func.h"
#include "item.h"

// сравнение цены, результат: меньше
START_TEST(cmp_int_lt)
{
    item_t a = { .prise = 10 };
    item_t b = { .prise = 20 };
    ck_assert_int_lt(cmp_item_by_prise(&a, &b), 0);
}
END_TEST

// сравнение цены, результат: больше
START_TEST(cmp_int_gt)
{
    item_t a = { .prise = 40 };
    item_t b = { .prise = 20 };
    ck_assert_int_gt(cmp_item_by_prise(&a, &b), 0);
}
END_TEST

// сравнение цены, результат: равны
START_TEST(cmp_int_eq)
{
    item_t a = { .prise = 20 };
    item_t b = { .prise = 20 };
    ck_assert_int_eq(cmp_item_by_prise(&a, &b), 0);
}
END_TEST

// сравнение веса, результат: меньше
START_TEST(cmp_float_lt)
{
    item_t a = { .weight = 10 };
    item_t b = { .weight = 20 };
    ck_assert_int_lt(cmp_item_by_weight(&a, &b), 0);
}
END_TEST

// сравнение веса, результат: больше
START_TEST(cmp_float_gt)
{
    item_t a = { .weight = 40 };
    item_t b = { .weight = 20 };
    ck_assert_int_gt(cmp_item_by_weight(&a, &b), 0);
}
END_TEST

// сравнение веса, результат: равны
START_TEST(cmp_float_eq)
{
    item_t a = { .weight = 20 };
    item_t b = { .weight = 20 };
    ck_assert_int_eq(cmp_item_by_weight(&a, &b), 0);
}
END_TEST

// сравнение названия, результат: меньше
START_TEST(cmp_str_lt)
{
    item_t a = { .title = "apple" };
    item_t b = { .title = "nice" };
    ck_assert_int_lt(cmp_item_by_title(&a, &b), 0);
}
END_TEST

// сравнение названия, результат: больше
START_TEST(cmp_str_gt)
{
    item_t a = { .title = "yes" };
    item_t b = { .title = "nice" };
    ck_assert_int_gt(cmp_item_by_title(&a, &b), 0);
}
END_TEST

// сравнение названия, результат: равны 
START_TEST(cmp_str_eq)
{
    item_t a = { .title = "apple" };
    item_t b = { .title = "apple" };
    ck_assert_int_eq(cmp_item_by_title(&a, &b), 0);
}
END_TEST


TCase *cmp_func_tcase(void)
{
    TCase *tc = tcase_create("cmp_func");
    
    tcase_add_test(tc, cmp_int_lt);
    tcase_add_test(tc, cmp_int_gt);
    tcase_add_test(tc, cmp_int_eq);
    
    tcase_add_test(tc, cmp_float_lt);
    tcase_add_test(tc, cmp_float_gt);
    tcase_add_test(tc, cmp_float_eq);
    
    tcase_add_test(tc, cmp_str_lt);
    tcase_add_test(tc, cmp_str_gt);
    tcase_add_test(tc, cmp_str_eq);

    return tc;
}
