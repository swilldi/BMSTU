#include "associative_array.h"
#include "check_unit_tests.h"
#include <check.h>
#include <stdio.h>

Suite *all_tests(void)
{
    Suite *s = suite_create("all_tests");

    suite_add_tcase(s, remove_tcase());
    suite_add_tcase(s, insert_tcase());
    suite_add_tcase(s, max_min_tcase());
    suite_add_tcase(s, find_tcase());
    suite_add_tcase(s, other_tcase());

    return s;
}

int main(void)
{
    Suite *s = all_tests();
    SRunner *sr = srunner_create(s);

    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_VERBOSE);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (num_failed == 0) ? 0 : 1;
}

// void add_one(const char *str, int *num, void *param);
// void print_elem(const char *str, int *num, void *param)
// {
//     (void)param;
//     printf("%s: %d\n", str, *num);
// }

// int main(void)
// {

//     assoc_array_t arr = assoc_array_create();
//     int rc;
//     (void) rc;
//     rc = assoc_array_insert(arr, "white", 255);
//     rc = assoc_array_insert(arr, "black", 0);
//     rc = assoc_array_insert(arr, "green", 125);
//     rc = assoc_array_insert(arr, "blue", 200);

//     int *finded_value;
//     rc = assoc_array_find(arr, "white", &finded_value);
//     printf("rc = %d, v = %d\n", rc, *finded_value);
//     rc = assoc_array_find(arr, "black", &finded_value);
//     printf("rc = %d, v = %d\n", rc, *finded_value);
//     rc = assoc_array_find(arr, "green", &finded_value);
//     printf("rc = %d, v = %d\n", rc, *finded_value);
//     rc = assoc_array_find(arr, "blue", &finded_value);
//     printf("rc = %d, v = %d\n", rc, *finded_value);

//     assoc_array_each(arr, print_elem, NULL);
//     printf("\n");
//     // assoc_array_each(arr, add_one, NULL);
//     assoc_array_remove(arr, "green");
//     rc = assoc_array_insert(arr, "red", 1232);
//     assoc_array_each(arr, print_elem, NULL);

//     assoc_array_destroy(&arr);
// }
