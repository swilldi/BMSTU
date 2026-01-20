#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#include "item_struct.h"
#include <stdio.h>

int is_number(char *str);
int read_file(FILE *f, item_t *arr, size_t *item_count);
void write_file(FILE *f, item_t arr[], size_t n);

#endif
