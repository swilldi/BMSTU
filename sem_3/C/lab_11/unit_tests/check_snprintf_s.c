#include <string.h>
#include <stdio.h>
#include <check.h>
#include "check_unit_tests.h"

#include "my_string.h"


// Вставка в начало
START_TEST(spec_in_start)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "%s Hello!", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "%s Hello!", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Вставка в конец
START_TEST(spec_in_end)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "Hello! %s", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "Hello! %s", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Вставка в середину
START_TEST(spec_in_med)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "Hello, %s, nice news", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "Hello, %s, nice news", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Вставка прямо перед текстом
START_TEST(spec_before_text)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "%sSomeText", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "%sSomeText", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Вставка внутри текста
START_TEST(spec_in_text)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "SomeText%s", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "SomeText%s", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Вставка прямо после текстом
START_TEST(spec_after_text)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "SomeText%s", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "SomeText%s", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Два спецификатора вместе
START_TEST(spec_plus_spec)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "%s%s", "some_test", " continue");
    size_t b_n = snprintf(b_str, STR_LEN, "%s%s", "some_test", " continue");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Два спецификатора около текста
START_TEST(specs_around_text)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "%s SomeText %s", "start", "end");
    size_t b_n = snprintf(b_str, STR_LEN, "%s SomeText %s", "start", "end");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Только один спецификатор
START_TEST(only_spec)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "%s", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "%s", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Длины строки не достаточно для полной вставки 
START_TEST(spec_str_overflow)
{
    #define STR_LEN 15
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "test_str: %s", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "test_str: %s", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// После вставки строка полностью заполнена
START_TEST(spec_full)
{
    #define STR_LEN 20
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "test_str: %s", "some_test");
    size_t b_n = snprintf(b_str, STR_LEN, "test_str: %s", "some_test");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Нулевая длина
START_TEST(zero_len)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, 0, "some_text");
    size_t b_n = snprintf(b_str, 0, "some_text");

    ck_assert(a_n == b_n);
    #undef STR_LEN 
}
END_TEST


TCase* tcase_snprintf_s(void)
{
    TCase *tc = tcase_create("snprintf_s");

    tcase_add_test(tc, spec_in_start);
    tcase_add_test(tc, spec_in_end);
    tcase_add_test(tc, spec_in_med);
    tcase_add_test(tc, spec_before_text);
    tcase_add_test(tc, spec_in_text);
    tcase_add_test(tc, spec_after_text);
    tcase_add_test(tc, spec_plus_spec);
    tcase_add_test(tc, specs_around_text);
    tcase_add_test(tc, only_spec);
    tcase_add_test(tc, spec_str_overflow);
    tcase_add_test(tc, spec_full);
    tcase_add_test(tc, zero_len);

    return tc;
}
