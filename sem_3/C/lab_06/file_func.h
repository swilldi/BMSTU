#ifndef FILE_FUNC_H
#define FILE_FUNC_H

#include "array_func.h"
#include "errors_code.h"
#include "file_func.h"
#include "struct_movie.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_str(FILE *file, char *str, size_t max_len);
int read_struct(FILE *file, movie_t *movie);
int read_structs_to_array(FILE *file, movie_t arr[], size_t *count, field sort_field);
int is_number(char *str);

#endif
