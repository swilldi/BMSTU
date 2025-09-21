#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#include <stdio.h>
#include "exit_code.h"
#include <stdbool.h>

int count_nums(FILE *f, size_t *count);
int read_array(FILE *f, int *pb, int *pe);
void write_array(FILE *f, int *pb, int *pe);
bool file_is_empty(FILE *f);

#endif
