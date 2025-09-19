#ifndef FILE_FUNC_H
#define FILE_FUNC_H

#include "file_func.h"
#include "struct_movie.h"
#include "errors_code.h"
#include "array_func.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int read_str(FILE* file, char *str, size_t max_len);
int read_struct(FILE *file, movie_t* movie);
int read_structs_to_array(FILE* file, movie_t arr[], size_t* count, field sort_field);
int is_number(char* str);


#endif
