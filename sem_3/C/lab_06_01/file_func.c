#include "file_func.h"
#include "struct_movie.h"
#include "errors_code.h"
#include "array_func.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 32
#define YEAR_SIZE 10


int read_str(FILE* file, char *str, size_t max_len) {
    if (fgets(str, max_len, file) == NULL)
        return READ_ERROR;
    if (strlen(str) >= max_len - 1)
        return OVERFLOW_STR;

    str[strcspn(str, "\t\n")] = '\0';
    return OK;
}

int read_struct(FILE *file, movie_t* movie) {
    int rc;
    char buffer[BUFFER_SIZE];

    // чтение имени
    rc = read_str(file, buffer, MOVIE_TITLE_LEN);
    if (rc != OK)
        return rc;
    strcpy(movie->title, buffer);

    // чтение фамилии
    rc = read_str(file, buffer, SURNAME_DIRECTOR_LEN);
    if (rc != OK)
        return rc;
    strcpy(movie->director, buffer);

    // чтение года
    rc = read_str(file, buffer, YEAR_SIZE);
    if (rc != OK)
        return rc;
    if (!is_number(buffer))
        return INVALID_CONTENT;
    movie->year = atol(buffer);

    return OK;
}

int read_structs_to_array(FILE *file, movie_t arr[], size_t *count, field sort_field) {
    *count = 0;
    int rc;
    movie_t movie;
    for (rc = read_struct(file, &movie); rc == OK; rc = read_struct(file, &movie))
    {
        if (*count == 15)
        {
            rc = STRUCTS_OVERFLOW;
            break;
        }

        insert_sorted_by_field(&movie, arr, *count, sort_field);
        (*count)++;
    }

    if (rc == READ_ERROR && feof(file))
        return OK;
    else
        return rc;
}

int is_number(char* str) {
    for (size_t i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}
