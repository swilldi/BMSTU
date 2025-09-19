#include "io_func.h"
#include "stdio.h"

void print_structs(movie_t arr[], size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("name: %s\ndirector: %s\nyear: %d\n", arr[i].title, arr[i].director, arr[i].year);
        // printf("%s\n%s\n%d\n", arr[i].title, arr[i].director, arr[i].year);
    }
}

void print_struct(movie_t *movie)
{
    printf("name: %s\ndirector: %s\nyear: %d\n", movie->title, movie->director, movie->year);
    // printf("%s\n%s\n%d\n", movie->title, movie->director, movie->year);
}
