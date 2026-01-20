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

int is_empty_str(char *str);
int read_year(FILE *file, int *year);
int read_str(FILE *file, char **str);
int read_struct(FILE *file, movie_t *movie);
int read_structs_to_array(FILE *file, movie_t arr[], size_t count, field sort_field);
size_t count_line_in_file(FILE *file);

#endif
