#include "associative_array.h"
#include "check_unit_tests.h"
#include <check.h>

void add_one(const char *key, int *num, void *param)
{
    (void)key;
    (void)param;
    (*num) += 1;
}

// очищение всех значений
START_TEST(clear_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc;
    rc = assoc_array_insert(arr, "white", 255);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "black", 0);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "green", 125);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "blue", 200);
    ck_assert(rc == ASSOC_ARRAY_OK);

    rc = assoc_array_clear(arr);
    ck_assert(rc == ASSOC_ARRAY_OK);
    assoc_array_destroy(&arr);
}
END_TEST

// очищение всех значений, некоректное значение массива
START_TEST(clear_invalid_param)
{
    int rc;
    rc = assoc_array_clear(NULL);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Увеличение каждого значения на 1
START_TEST(each_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc;
    rc = assoc_array_insert(arr, "white", 255);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "black", 0);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "green", 125);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "blue", 200);
    ck_assert(rc == ASSOC_ARRAY_OK);

    rc = assoc_array_each(arr, add_one, NULL);
    ck_assert(rc == ASSOC_ARRAY_OK);

    int *finded_value;
    rc = assoc_array_find(arr, "white", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 256);
    rc = assoc_array_find(arr, "black", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 1);
    rc = assoc_array_find(arr, "green", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 126);
    rc = assoc_array_find(arr, "blue", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 201);

    assoc_array_destroy(&arr);
}
END_TEST

// Некоректная передача массива
START_TEST(each_invalid_param_arr)
{
    int rc;
    rc = assoc_array_each(NULL, add_one, NULL);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

// Некоректная передача указателя на функцию
START_TEST(each_invalid_func)
{
    assoc_array_t arr = assoc_array_create();
    int rc;
    rc = assoc_array_insert(arr, "white", 255);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "black", 0);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "green", 125);
    ck_assert(rc == ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "blue", 200);
    ck_assert(rc == ASSOC_ARRAY_OK);

    rc = assoc_array_each(arr, NULL, NULL);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}
END_TEST

TCase *other_tcase(void)
{
    TCase *tc = tcase_create("other_func");

    tcase_add_test(tc, clear_arr);
    tcase_add_test(tc, clear_invalid_param);
    tcase_add_test(tc, each_arr);
    tcase_add_test(tc, each_invalid_param_arr);
    tcase_add_test(tc, each_invalid_func);

    return tc;
}
