#include "associative_array.h"
#include "check_unit_tests.h"
#include <check.h>

#include "stdio.h"
START_TEST(insert_in_empty_arr)
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
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 255);
    rc = assoc_array_find(arr, "black", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 0);
    rc = assoc_array_find(arr, "green", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 125);
    rc = assoc_array_find(arr, "blue", &finded_value);
    ck_assert(rc == ASSOC_ARRAY_OK && *finded_value == 200);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(insert_exist_key)
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

    rc = assoc_array_insert(arr, "black", 12);
    ck_assert(rc == ASSOC_ARRAY_KEY_EXISTS);

    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(insert_invalid_param)
{
    int rc;
    rc = assoc_array_insert(NULL, "black", 12);
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

TCase *insert_tcase(void)
{
    TCase *tc = tcase_create("insert_func");

    tcase_add_test(tc, insert_in_empty_arr);
    tcase_add_test(tc, insert_exist_key);
    tcase_add_test(tc, insert_invalid_param);

    return tc;
}
