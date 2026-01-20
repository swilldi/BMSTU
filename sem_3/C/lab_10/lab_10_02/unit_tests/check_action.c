#include <check.h>
#include <math.h>

#include "check_unit_tests.h"
#include "action.h"


// Строка out
START_TEST(str_to_out)
{
    char *str = "out";
    action_t act = str_to_action(str);
    ck_assert(act == OUT);
}
END_TEST

// Строка div
START_TEST(str_to_div)
{
    char *str = "div";
    action_t act = str_to_action(str);
    ck_assert(act == DIV);
}
END_TEST

// Строка mul
START_TEST(str_to_mul)
{
    char *str = "mul";
    action_t act = str_to_action(str);
    ck_assert(act == MUL);
}
END_TEST
// Строка no_action
START_TEST(str_to_err)
{
    char *str = "asd";
    action_t act = str_to_action(str);
    ck_assert(act == ACTION_ERR);
}
END_TEST



TCase *list_tcase(void)
{
    TCase *tc = tcase_create("action");
    
    tcase_add_test(tc, str_to_div);
    tcase_add_test(tc, str_to_mul);
    tcase_add_test(tc, str_to_out);
    tcase_add_test(tc, str_to_err);
    
    return tc;
}
