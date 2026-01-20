#include "associative_array.h"
#include "check_unit_tests.h"
#include <check.h>

// Удаление из массива
START_TEST(remove_from_arr)
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

    rc = assoc_array_remove(arr, "black");
    ck_assert(rc == ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

// Удаление единственного значения из массива
START_TEST(remove_from_arr_one_elem)
{
    assoc_array_t arr = assoc_array_create();
    int rc;
    rc = assoc_array_insert(arr, "black", 0);
    ck_assert(rc == ASSOC_ARRAY_OK);

    rc = assoc_array_remove(arr, "black");
    ck_assert(rc == ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}
END_TEST

// Удаление по несуществующему ключу
START_TEST(remove_from_arr_not_exits)
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

    rc = assoc_array_remove(arr, "red");
    ck_assert(rc == ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

// Удалиние, передается некоректный массив
START_TEST(remove_invalid_param)
{
    int rc;

    rc = assoc_array_remove(NULL, "black");
    ck_assert(rc == ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST

TCase *remove_tcase(void)
{
    TCase *tc = tcase_create("remove_func");

    tcase_add_test(tc, remove_from_arr);
    tcase_add_test(tc, remove_from_arr_one_elem);
    tcase_add_test(tc, remove_from_arr_not_exits);
    tcase_add_test(tc, remove_invalid_param);

    return tc;
}
