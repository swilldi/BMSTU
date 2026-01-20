#include "check_unit_tests.h"
#include <stdio.h>

Suite *all_tests(void)
{
    Suite *s = suite_create("all_tests");

    suite_add_tcase(s, add_after_even_tcase());
    suite_add_tcase(s, fill_prime_num_tcase());

    return s;
}

int main(void)
{
    Suite *s = all_tests();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (num_failed == 0) ? 0 : 1;
}
