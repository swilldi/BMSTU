#include "array_func.h"
#include "file_func.h"
#include "io_func.h"
#include "sort_field.h"
#include "struct_movie.h"
#include <stdio.h>
#include "checkers.h"

#define MAX_STURCT_IN_FILE 15

int main(int argc, char **argv)
{
    // количество аргументов
    if (argc < 3)
    {
        //printf("Args too few\n");
        return ARGS_TOO_FEW;
    }
        

    // поле корректное
    field sort_field = is_available_field(argv[2]);
    if (sort_field == 10)
    {
        //printf("invalid args: not field\n");
        return INVALID_ARGS;
    }
        
    if (argc > 3 && sort_field == YEAR && !is_number(argv[3]))
    {
        //printf("invalid args: year\n");
        return INVALID_ARGS;
    }

    // открытие файла
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        //printf("Error while openinig file\n");
        return FILE_OPEN_ERROR;
    }
        

    if (is_empty_file(file))
    {
        //printf("File is empty\n");
        return FILE_IS_EMPTY;
    }

    // заполнение массива
    movie_t movies[MAX_STURCT_IN_FILE];
    size_t count = 0;
    int rc = read_structs_to_array(file, movies, &count, sort_field);
    if (rc != 0)
    {
        //printf("Error while reading data from file\n");
        return rc;
    }

    // вывод содержимого файла или структуры по ключу
    if (argc > 3)
    {
        field_value value;
        if (sort_field == TITLE || sort_field == DIRECTOR)
            value.str = argv[3];
        else
            value.num = atol(argv[3]);
        size_t i = binary_search_by_field(&value, movies, count, sort_field);

        if (i == (size_t)-1)
            printf("Not found\n");
        else
            print_struct(&movies[i]);
    }
    else
    {
        print_structs(movies, count);
    }

    fclose(file);
}
