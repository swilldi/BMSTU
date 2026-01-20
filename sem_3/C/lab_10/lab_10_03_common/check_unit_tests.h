#ifndef CHECK_UNIT_TESTS_H__
#define CHECK_UNIT_TESTS_H__

#define EPS 1e-5

#include <check.h>

TCase *find_tcase(void);
TCase *remove_tcase(void);
TCase *insert_tcase(void);
TCase *max_min_tcase(void);
TCase *other_tcase(void);

#endif
