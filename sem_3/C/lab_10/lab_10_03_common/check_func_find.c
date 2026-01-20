#include "associative_array.h"
#include "check_unit_tests.h"
#include <check.h>

// Поиск значения в начале массива
START_TEST(value_in_array_begin)
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

    int *finded_value;
    rc = assoc_array_find(arr, "white", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK);

    ck_assert(*finded_value == 255);
    assoc_array_destroy(&arr);
}
END_TEST

// Поиск значения в середине массива
START_TEST(value_in_array_med)
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

    int *finded_value;
    rc = assoc_array_find(arr, "green", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK);

    ck_assert(*finded_value == 125);
    assoc_array_destroy(&arr);
}
END_TEST

// Поиск значения в конце массива
START_TEST(value_in_array_end)
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

    int *finded_value;
    rc = assoc_array_find(arr, "blue", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK);

    ck_assert(*finded_value == 200);
    assoc_array_destroy(&arr);
}
END_TEST

// Значения нет в массиве
START_TEST(value_not_in_array)
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

    int *finded_value;
    rc = assoc_array_find(arr, "red", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}
END_TEST

// Пустой массив
START_TEST(empty_array)
{
    assoc_array_t arr = assoc_array_create();
    int rc;

    int *finded_value;
    rc = assoc_array_find(arr, "red", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}
END_TEST

// Некоректные данные в качестве параметор
START_TEST(find_invalid_param)
{
    int rc;

    int *finded_value;
    rc = assoc_array_find(NULL, "red", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

TCase *find_tcase(void)
{
    TCase *tc = tcase_create("find_func");

    tcase_add_test(tc, value_in_array_begin);
    tcase_add_test(tc, value_in_array_med);
    tcase_add_test(tc, value_in_array_end);
    tcase_add_test(tc, value_not_in_array);
    tcase_add_test(tc, empty_array);
    tcase_add_test(tc, find_invalid_param);

    return tc;
}
