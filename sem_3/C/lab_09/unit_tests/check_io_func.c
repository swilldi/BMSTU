#include "check_unit_tests.h"
#include <check.h>

#include "file_func.h"
#include "movie_func.h"

// стениче короткой строки, т.е. при чтении НЕ будет вызван realloc
START_TEST(check_read_short_str)
{
    int rc = OK;
    FILE *f = fopen("./unit_tests/files/short_str.txt", "r");
    
    char *str_file = NULL;
    rc = read_str(f, &str_file);
    ck_assert_int_eq(rc, OK);
    char *cur_str = "123";

    ck_assert_str_eq(str_file, cur_str);

    free(str_file);
    fclose(f);
}
END_TEST

// чтениче длинной строки, т.е. при чтении будет вызван realloc
START_TEST(check_read_long_str)
{
    int rc;
    FILE *f = fopen("./unit_tests/files/long_str.txt", "r");
    
    char *str_file = NULL;
    rc = read_str(f, &str_file);
    ck_assert_int_eq(rc, OK);
    char *cur_str = "123456789012345678901234567890";

    ck_assert_str_eq(str_file, cur_str);

    free(str_file);
    fclose(f);
}
END_TEST

// чтение полной структуры: успешно
START_TEST(ok_read_struct)
{
    FILE *f = fopen("./unit_tests/files/ok_struct.txt", "r");
    
    movie_t movie = { 0 };
    int rc = read_struct(f, &movie);

    ck_assert_uint_eq(rc, OK);
    ck_assert_str_eq(movie.title, "title");
    ck_assert_str_eq(movie.director, "name");
    ck_assert_int_eq(movie.year, 1000);

    free_movie_content(&movie);
    fclose(f);
}
END_TEST
// чтение полной структуры: пустая строка названия
START_TEST(empty_title_struct)
{
    FILE *f = fopen("./unit_tests/files/empty_title_struct.txt", "r");
    
    movie_t movie = { 0 };
    int rc = read_struct(f, &movie);

    ck_assert_uint_eq(rc, EMPTY_STR);

    fclose(f);
}
END_TEST
// чтение полной структуры: пустая строка фамилии
START_TEST(empty_name_struct)
{
    FILE *f = fopen("./unit_tests/files/empty_name_struct.txt", "r");
    
    movie_t movie = { 0 };
    int rc = read_struct(f, &movie);

    ck_assert_uint_eq(rc, EMPTY_STR);

    fclose(f);
}
END_TEST
// чтение полной структуры: год не число
START_TEST(year_not_num_struct)
{
    FILE *f = fopen("./unit_tests/files/year_not_num_struct.txt", "r");
    
    movie_t movie = { 0 };
    int rc = read_struct(f, &movie);

    ck_assert_uint_eq(rc, NOT_NUM);

    fclose(f);
}
END_TEST
// чтение полной структуры: год отрицательный
START_TEST(not_natur_num_struct)
{
    FILE *f = fopen("./unit_tests/files/not_natur_num_struct.txt", "r");
    
    movie_t movie = { 0 };
    int rc = read_struct(f, &movie);

    ck_assert_uint_eq(rc, NOT_NATURAL_NUM);

    fclose(f);
}
END_TEST


TCase *file_func_tcase(void)
{
    TCase *tc = tcase_create("file_func");
    tcase_add_test(tc, check_read_short_str);
    tcase_add_test(tc, check_read_long_str);
    tcase_add_test(tc, ok_read_struct);
    tcase_add_test(tc, empty_title_struct);
    tcase_add_test(tc, empty_name_struct);
    tcase_add_test(tc, year_not_num_struct);
    tcase_add_test(tc, not_natur_num_struct);

    return tc;
}
