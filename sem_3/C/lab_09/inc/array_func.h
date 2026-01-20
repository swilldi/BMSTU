#include "errors_code.h"
#include "sort_field.h"
#include "struct_movie.h"
#include <stdlib.h>
#include <string.h>

int compare_movie_by_field(const movie_t *a, const movie_t *b, field sort_field);

int compare_value_by_field(const movie_t *movie, const field_value *value, field compared_field);

void insert_sorted_by_field(movie_t *movie, movie_t *arr, size_t count, field sort_field);
size_t binary_search_by_field(const field_value *value, const movie_t *arr, size_t count, field search_field);
void movie_copy(movie_t *movie, movie_t *source_movie);
