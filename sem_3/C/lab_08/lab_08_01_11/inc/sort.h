#ifndef SORT_H__
#define SORT_H__

#include <stdlib.h>
#include <string.h>
#include "exit_code.h"

typedef int(*comparator_t)(const void *, const void *);

int mysort(void *pbeg, size_t count, size_t size, comparator_t cmp);
int swap(void *a, void *b, size_t size);
int cmp_int(const void *a, const void *b);
int cmp_double(const void *a, const void *b);
int cmp_str(const void *a, const void *b);

#endif
