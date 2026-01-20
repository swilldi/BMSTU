#include "check_unit_tests.h"
#include <check.h>
#include <stdbool.h>
#include "array_func.h"
#include "movie_func.h"

START_TEST(insert_in_end)
{
    movie_t arr_tmp[4] = 
    {
        { "t_1", "n_1", 100 },
        { "t_2", "n_2", 200 },
        { "t_3", "n_3", 300 }
    };

    movie_t *arr = create_movie_arr(4);
    for (size_t i = 0; i < 3; i++)
        movie_copy(&arr[i], &arr_tmp[i]);

    movie_t out_arr[4] = 
    {
        { "t_1", "n_1", 100 },
        { "t_2", "n_2", 200 },
        { "t_3", "n_3", 300 },
        { "t_5", "n_5", 500 }
    };

    movie_t new_elem = { "t_5", "n_5", 500 };

    insert_sorted_by_field(&new_elem, (movie_t*)arr, 3, TITLE);

    for (size_t i = 0; i < 4; i++)
    {
        ck_assert_str_eq(arr[i].director, out_arr[i].director);
        ck_assert_str_eq(arr[i].title, out_arr[i].title);
        ck_assert_uint_eq(arr[i].year, out_arr[i].year);
    }

    free_movie_arr_content(arr, 4);
    free(arr);
}
END_TEST

START_TEST(insert_in_begin)
{
    movie_t arr_tmp[] = 
    {
        { "t_1", "n_1", 100 },
        { "t_2", "n_2", 200 },
        { "t_3", "n_3", 300 }
    };

    movie_t *arr = create_movie_arr(4);
    for (size_t i = 0; i < 3; i++)
        movie_copy(&arr[i], &arr_tmp[i]);

    movie_t out_arr[4] = 
    {
        { "t", "n", 500 },
        { "t_1", "n_1", 100 },
        { "t_2", "n_2", 200 },
        { "t_3", "n_3", 300 }
    };

    movie_t new_elem = { "t", "n", 500 };

    insert_sorted_by_field(&new_elem, (movie_t*)arr, 3, TITLE);

    for (size_t i = 0; i < 4; i++)
    {
        ck_assert_str_eq(arr[i].director, out_arr[i].director);
        ck_assert_str_eq(arr[i].title, out_arr[i].title);
        ck_assert_uint_eq(arr[i].year, out_arr[i].year);
    }

    free_movie_arr_content(arr, 4);
    free(arr);
}
END_TEST

START_TEST(insert_in_med)
{
    movie_t arr_tmp[3] = 
    {
        { "t_1", "n_1", 100 },
        { "t_3", "n_3", 300 },
        { "t_5", "n_2", 200 }
    };

    movie_t *arr = create_movie_arr(4);
    for (size_t i = 0; i < 3; i++)
        movie_copy(&arr[i], &arr_tmp[i]);

    movie_t out_arr[4] = 
    {
        { "t_1", "n_1", 100 },
        { "t_2", "n_10", 500 },
        { "t_3", "n_3", 300 },
        { "t_5", "n_2", 200 }
    };

    movie_t new_elem = { "t_2", "n_10", 500 };

    insert_sorted_by_field(&new_elem, (movie_t*)arr, 3, TITLE);

    for (size_t i = 0; i < 4; i++)
    {
        ck_assert_str_eq(arr[i].director, out_arr[i].director);
        ck_assert_str_eq(arr[i].title, out_arr[i].title);
        ck_assert_uint_eq(arr[i].year, out_arr[i].year);
    }

    free_movie_arr_content(arr, 4);
    free(arr);
}
END_TEST

TCase *insert_tcase(void)
{
    TCase *tc = tcase_create("sort");

    tcase_add_test(tc, insert_in_end);
    tcase_add_test(tc, insert_in_begin);
    tcase_add_test(tc, insert_in_med);


    return tc;
}
