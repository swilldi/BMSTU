#include "associative_array.h"
#include "check_unit_tests.h"
#include <check.h>

START_TEST(get_min)
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

    int *value_by_min_key;
    rc = assoc_array_min(arr, &value_by_min_key);
    ck_assert(rc == ASSOC_ARRAY_OK && *value_by_min_key == 0);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(get_max)
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

    int *value_by_min_key;
    rc = assoc_array_max(arr, &value_by_min_key);
    ck_assert(rc == ASSOC_ARRAY_OK && *value_by_min_key == 255);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(get_min_invalid_param_arr)
{
    int rc;
    int *value_by_min_key;
    rc = assoc_array_min(NULL, &value_by_min_key);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(get_max_invalid_param_arr)
{
    int rc;
    int *value_by_min_key;
    rc = assoc_array_max(NULL, &value_by_min_key);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

START_TEST(get_min_invalid_param_value)
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

    rc = assoc_array_min(arr, NULL);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(get_max_invalid_param_value)
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

    rc = assoc_array_max(arr, NULL);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(get_min_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc;

    int *value_by_min_key;
    rc = assoc_array_min(arr, &value_by_min_key);
    ck_assert(rc == ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(get_max_empty_arr)
{
    assoc_array_t arr = assoc_array_create();
    int rc;

    int *value_by_min_key;
    rc = assoc_array_max(arr, &value_by_min_key);
    ck_assert(rc == ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

TCase *max_min_tcase(void)
{
    TCase *tc = tcase_create("max_min_func");

    tcase_add_test(tc, get_min);
    tcase_add_test(tc, get_max);
    tcase_add_test(tc, get_min_invalid_param_arr);
    tcase_add_test(tc, get_max_invalid_param_arr);
    tcase_add_test(tc, get_min_invalid_param_value);
    tcase_add_test(tc, get_max_invalid_param_value);
    tcase_add_test(tc, get_min_empty_arr);
    tcase_add_test(tc, get_max_empty_arr);

    return tc;
}
