#ifndef MOVIE_FUNC_H__
#define MOVIE_FUNC_H__

#include <struct_movie.h>
#include "stdlib.h"

movie_t *create_movie_arr(size_t count);
void free_movie_arr_content(movie_t *arr, size_t count);
void free_movie_content(movie_t *movie);

#endif
