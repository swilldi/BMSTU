#include "file_func.h"
#include "array_func.h"
#include "errors_code.h"
#include "struct_movie.h"
#include "checkers.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define YEAR_SIZE 10

int is_empty_str(char *str)
{
    for (char *symbol = str; *symbol != '\0' && *symbol != '\n'; symbol++)
    {
        if (!isspace(*symbol))
            return 0;
    }    
    return 1;
}

int read_str(FILE *file, char *str, size_t max_len)
{
    if (fgets(str, max_len + 1, file) == NULL)
        return READ_ERROR;
    if (strlen(str) > max_len)
        return OVERFLOW_STR;
    if (is_empty_str(str))
        return EMPTY_STR;

    str[strcspn(str, "\t\n")] = '\0';
    return OK;
}

int read_struct(FILE *file, movie_t *movie)
{
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

int read_structs_to_array(FILE *file, movie_t arr[], size_t *count, field sort_field)
{
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


