#include <string.h>
#include <stdio.h>
#include <check.h>
#include <limits.h>

#include "check_unit_tests.h"
#include "my_string.h"


// Первый %s, далее %llx
START_TEST(spec_s_before_llx)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "My name is %s. I like number %llx", "Dima", 25ll);
    size_t b_n = snprintf(b_str, STR_LEN, "My name is %s. I like number %llx", "Dima", 25ll);

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Первый %llx, далее %s
START_TEST(spec_llx_before_s)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "I like number %llx. My name is %s", 25ll, "Dima");
    size_t b_n = snprintf(b_str, STR_LEN, "I like number %llx. My name is %s", 25ll, "Dima");

    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST

// Спецификаторы подряд (%s%llx)
START_TEST(spec_joined)
{
    #define STR_LEN 128
    char a_str[STR_LEN];
    char b_str[STR_LEN];

    size_t a_n = my_snprintf(a_str, STR_LEN, "%s%llx", "Number: ", 25ll);
    size_t b_n = snprintf(b_str, STR_LEN, "%s%llx", "Number: ", 25ll);


    ck_assert(a_n == b_n);
    ck_assert_str_eq(a_str, b_str);
    #undef STR_LEN 
}
END_TEST




TCase* tcase_snprintf_common(void)
{
    TCase *tc = tcase_create("snprintf_common");

    tcase_add_test(tc, spec_s_before_llx);
    tcase_add_test(tc, spec_llx_before_s);
    tcase_add_test(tc, spec_joined);

    return tc;
}
