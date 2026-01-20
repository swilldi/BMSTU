#include "arr_func.h"
#include "exit_code.h"
#include "file_func.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_err_msg(int rc)
{
    char *msg;

    switch (rc)
    {
        case TOO_FEW_ARGS:
            msg = "Слишком мало аргументов";
            break;
        case INVALID_ARGS:
            msg = "Неверные аргументы";
            break;
        case OPEN_FILE_ERROR:
            msg = "Ошибка открытия файла";
            break;
        case INVALID_FILE_CONTENT:
            msg = "В файле содержатся не только числа";
            break;
        case EMPTY_FILE:
            msg = "Пустой файл";
            break;
        case MALLOC_ERROR:
            msg = "Ошибка выделения памяти";
            break;
        case EMPTY_ARR:
            msg = "После фильтрации массив пустой";
            break;
        default:
            msg = "Неизвестная ошибка";
            break;
    }

    printf("%s", msg);
}

bool validate_key(char *key)
{
    return strlen(key) == 1 && *key == 'f';
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return TOO_FEW_ARGS;
    else if (argc > 4)
        return TOO_MUCH_ARGS;

    bool key_is_valid = false;
    if (argc == 4)
    {
        key_is_valid = validate_key(argv[3]);
    }
    if (argc == 4 && !key_is_valid)
    {
        print_err_msg(INVALID_ARGS);
        return INVALID_ARGS;
    }

    // открывам файл и считаем кол-во чисел
    int rc;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        print_err_msg(OPEN_FILE_ERROR);
        return OPEN_FILE_ERROR;
    }

    size_t count;
    rc = count_nums(f, &count);
    if (rc != OK)
    {
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    if (count == 0)
    {
        fclose(f);
        print_err_msg(EMPTY_ARR);
        return EMPTY_ARR;
    }

    int *arr_b = NULL, *arr_e;
    rc = create_arr(count, &arr_b, &arr_e);
    if (rc != OK)
    {
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    // читаем данные в файл
    rc = read_array(f, arr_b, arr_e);
    if (rc != OK)
    {
        free(arr_b);
        fclose(f);
        print_err_msg(rc);
        return rc;
    }

    fclose(f);

    // если есть ключ, выполнить фильтрацию
    if (argc > 3 && key_is_valid)
    {
        // Указатели на начало и конец отфилдьтрованного массива
        int *p_fab = NULL, *p_fae = NULL;
        rc = key(arr_b, arr_e, &p_fab, &p_fae);

        if (rc != OK)
        {
            free(arr_b);
            free(p_fab);
            arr_b = NULL;
            print_err_msg(rc);
            return rc;
        }

        rename_arr(&arr_b, &arr_e, &p_fab, &p_fae);
        count = arr_e - arr_b;
    }

    // сортировка
    mysort(arr_b, count, sizeof(int), cmp_int);

    // запись в файл
    f = fopen(argv[2], "w");
    write_array(f, arr_b, arr_e);

    // очишение памяти
    fclose(f);
    free(arr_b);
    arr_b = NULL;
}


