#ifndef SORT_H__
#define SORT_H__

#include <stdlib.h>
#include <string.h>
#include "exit_code.h"

typedef float(*comparator_t)(const void *, const void *);

int shaker_sort(void* pbeg, size_t count, size_t size, comparator_t cmp);
int bumble_sort(void* pbeg, size_t count, size_t size, comparator_t cmp);
void swap(void *a, void *b, size_t size, void *tmp);

float cmp_car_prise(const void *a, const void *b);
float cmp_car_prise_by_key(const void *a, const void *b);

#endif
