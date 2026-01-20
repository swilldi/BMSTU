#define _GNU_SOURCE
#include "file_func.h"
#include "array_func.h"
#include "checkers.h"
#include "errors_code.h"
#include "movie_func.h"
#include "struct_movie.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 32
#define YEAR_SIZE 10
#define MOVIE_FIELDS_COUNT 3

int is_empty_str(char *str)
{
    for (char *symbol = str; *symbol != '\0' && *symbol != '\n'; symbol++)
    {
        if (!isspace(*symbol))
            return 0;
    }
    return 1;
}

int read_year(FILE *file, int *year)
{
    long year_tmp;
    if (fscanf(file, "%ld", &year_tmp) != 1)
        return NOT_NUM;
    if (year_tmp <= 0)
        return NOT_NATURAL_NUM;

    *year = year_tmp;

    // очищение stdin от отсавшихся '\n'
    int ch = getc(file);
    while (ch != '\n' && ch != EOF)
        ch = getc(file);

    return OK;
}

int read_str(FILE *file, char **str)
{
    size_t len = 0;
    ssize_t read = getline(str, &len, file);
    if (read == -1)
        return READ_ERROR;
    if (is_empty_str(*str))
        return EMPTY_STR;

    (*str)[strcspn((*str), "\t\n")] = '\0';
    return OK;
}

int read_struct(FILE *file, movie_t *movie)
{
    int rc;

    // чтение имени
    rc = read_str(file, &movie->title);
    if (rc != OK)
    {
        if (rc != READ_ERROR)
            free(movie->title);
        return rc;
    }

    // чтение фамилии
    rc = read_str(file, &movie->director);
    if (rc != OK)
    {
        free(movie->title);
        if (rc != READ_ERROR)
            free(movie->director);
        return rc;
    }

    // чтение года
    rc = read_year(file, &movie->year);
    if (rc != OK)
    {
        free(movie->title);
        free(movie->director);
        return rc;
    }

    return OK;
}

int read_structs_to_array(FILE *file, movie_t *arr, size_t count, field sort_field)
{
    int rc = OK;
    movie_t movie_tmp = { 0 };
    size_t i = 0;

    for (; i < count; i++)
    {
        rc = read_struct(file, &movie_tmp);
        if (rc != OK)
            break;

        insert_sorted_by_field(&movie_tmp, arr, i, sort_field);
        free_movie_content(&movie_tmp);
    }

    if (rc == OK || (rc == READ_ERROR && feof(file)))
    {
        return OK;
    }
    else
    {
        free_movie_arr_content(arr, i);
        return rc;
    }
}

size_t count_line_in_file(FILE *file)
{
    fseek(file, 0, SEEK_SET);
    size_t line_count = 0;
    int ch;
    int last_ch = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
            line_count++;
        last_ch = ch;
    }

    if (last_ch != '\n' && last_ch != 0)
        line_count++;

    fseek(file, 0, SEEK_SET);
    return line_count;
}
