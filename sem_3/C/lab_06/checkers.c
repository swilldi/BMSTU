#include "struct_movie.h"
#include "errors_code.h"
#include "stdio.h"
#include "sort_field.h"
#include <ctype.h>
#include <string.h>

int is_available_field(char *str)
{
    int is_available = 10;

    if (strcmp("title", str) == 0)
    {
        if (strlen(str) > MOVIE_TITLE_LEN)
            return OVERFLOW_STR;
        is_available = TITLE;
    }
    else if (strcmp("name", str) == 0)
    {
        if (strlen(str) > SURNAME_DIRECTOR_LEN)
            return OVERFLOW_STR;
        is_available = DIRECTOR;
    }
    else if (strcmp("year", str) == 0)
    {
        is_available = YEAR;
    }
    return is_available;
}

int is_empty_file(FILE *file)
{
    size_t start = ftell(file);
    fseek(file, 0, SEEK_END);
    size_t end = ftell(file);
    rewind(file);

    return end - start == 0;
}

int is_number(char *str)
{
    for (size_t i = 0; str[i] != '\0' && str[i] != '\n'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}
