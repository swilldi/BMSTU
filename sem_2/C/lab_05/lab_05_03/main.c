#include "errors_code.h"
#include "file_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
--- Ключи и описани ---
import – txt -> bin
export – bin -> txt

p – print
s – sort
c – create


--- Содержимое ---
тип целого числа: int


--- Сортировка ---
Алгоритм сортировки: пузырек
Упорядочивание по: возрастанию


*/

int main(int argc, char **argv)
{
    // printf("%d\n", argc);
    if (argc < 3)
        return ARGS_TOO_FEW;

    FILE *file;
    // printf("|%s| -> %d\n", argv[1], strcmp(argv[1], "import"));

    if (strcmp(argv[1], "c") == 0)
    {
        file = fopen(argv[2], "wb");
        if (file == NULL)
            return FILE_OPEN_ERROR;

        int n = atol(argv[3]);

        create_random_file(file, n);
        fclose(file);
    }
    else if (strcmp(argv[1], "p") == 0)
    {
        file = fopen(argv[2], "rb");
        if (file == NULL)
            return FILE_OPEN_ERROR;
        if (is_empty(file) || check_content(file))
            return INVALID_CONTENT;
        print_content(file);
        fclose(file);
    }
    else if (strcmp(argv[1], "s") == 0)
    {
        file = fopen(argv[2], "rb+");
        if (file == NULL)
            return FILE_OPEN_ERROR;
        if (is_empty(file) || check_content(file))
            return INVALID_CONTENT;
        sort_file(file);
        fclose(file);
    }
    else if (strcmp(argv[1], "import") == 0)
    {
        if (argc < 4)
        {
            return ARGS_TOO_FEW;
        }

        file = fopen(argv[2], "r");
        if (file == NULL)
            return FILE_OPEN_ERROR;
        if (is_empty(file))
            return INVALID_CONTENT;
        FILE *bin_file = fopen(argv[3], "wb");

        txt_to_bin(file, bin_file);

        fclose(file);
        fclose(bin_file);
    }
    else if (strcmp(argv[1], "export") == 0)
    {
        if (argc < 4)
        {
            // printf("%d\n", argc);
            return ARGS_TOO_FEW;
        }

        file = fopen(argv[2], "rb");
        if (file == NULL)
            return FILE_OPEN_ERROR;
        if (is_empty(file) || check_content(file))
            return INVALID_CONTENT;

        FILE *txt_file = fopen(argv[3], "w");

        bin_to_txt(file, txt_file);

        fclose(file);
        fclose(txt_file);
    }
    else
        return INVALID_ARGS;
}
