#include "errors_code.h"
#include "sort_field.h"
#include "struct_movie.h"
#include <stdlib.h>
#include <string.h>

int compare_movie_by_field(const movie_t *a, const movie_t *b, field sort_field)
{
    switch (sort_field)
    {
        case TITLE:
            return strcmp(a->title, b->title);
        case DIRECTOR:
            return strcmp(a->director, b->director);
        default:
            return a->year - b->year;
    }
    return 100;
}

int compare_value_by_field(const movie_t *movie, const field_value *value, field compared_field)
{
    switch (compared_field)
    {
        case TITLE:
            return strcmp(movie->title, value->str);
        case DIRECTOR:
            return strcmp(movie->director, value->str);
        default:
            return movie->year - value->num;
    }
}

void insert_sorted_by_field(movie_t *movie, movie_t *arr, size_t count, field sort_field)
{
    size_t i = count;
    while (i != 0 && compare_movie_by_field(movie, &arr[i - 1], sort_field) < 0)
    {
        i--;
        arr[i + 1] = arr[i];
    }
    arr[i] = *movie;
}

size_t binary_search_by_field(const field_value *value, const movie_t *arr, size_t count, field search_field)
{
    int value_is_find = 0, compare_res;
    size_t l = 0, r = count - 1, med;
    while (l <= r && r <= count)
    {
        med = l + (r - l) / 2;

        compare_res = compare_value_by_field(&arr[med], value, search_field);
        if (compare_res < 0)
        {
            l = med + 1;
        }
        else if (compare_res > 0)
        {
            r = med - 1;
        }
        else
        {
            value_is_find = 1;
            break;
        }
    }
    return value_is_find ? med : (size_t)-1;
}
