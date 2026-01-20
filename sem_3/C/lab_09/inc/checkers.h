#ifndef CHECKERS_H__
#define CHECKERS_H__

#include "errors_code.h"
#include "sort_field.h"
#include "stdio.h"
#include "struct_movie.h"

int is_available_field(char *str);
int is_empty_file(FILE *file);
int is_number(char *str);

#endif
