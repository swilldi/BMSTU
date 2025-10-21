#include "check_unit_tests.h"
#include <stdio.h>

Suite* all_tests(void)
{
    Suite* st = suite_create("pos_tests");
    suite_add_tcase(st, create_tests_matrix_func());

    return st;
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
