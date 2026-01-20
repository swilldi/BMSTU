#include "movie_func.h"
#include "errors_code.h"
#include "file_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <struct_movie.h>

movie_t *create_movie_arr(size_t count)
{
    movie_t *arr = calloc(count, sizeof(movie_t));
    return arr;
}

void free_movie_arr_content(movie_t *arr, size_t count)
{
    for (size_t i = 0; i < count; i++)
        free_movie_content(&arr[i]);
}

void free_movie_content(movie_t *movie)
{
    free(movie->title);
    free(movie->director);
    movie->title = NULL;
    movie->director = NULL;
}
