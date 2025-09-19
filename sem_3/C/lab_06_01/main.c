#include <stdio.h>
#include "struct_movie.h"
#include "file_func.h"
#include "sort_field.h"
#include "io_func.h"
#include "array_func.h"


#define MAX_STURCT_IN_FILE 15

int is_available_field(char *str)
{
    const int available_fields_count = 3;
    char *available_fields[3] = {"title", "name", "year"};
    int is_available = 10;
    
    for (size_t i = 0; i < available_fields_count; i++)
    {
        if (strcmp(available_fields[i], str) == 0)
        {
            is_available = i;
            break;
        }
    }
    return is_available;
}

int main(int argc, char **argv) {
    // количество аргументов
    if (argc < 3)
        return ARGS_TOO_FEW;
    
    // поле корректное
    field sort_field = is_available_field(argv[2]);
    if (sort_field == 10)
        return INVALID_ARGS;

    // открытие файла
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        return FILE_OPEN_ERROR;
    
    // заполнение массива
    movie_t movies[MAX_STURCT_IN_FILE];
    size_t count = 0;
    int rc = read_structs_to_array(file, movies, &count, sort_field);
    if (rc != 0)
    {
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
