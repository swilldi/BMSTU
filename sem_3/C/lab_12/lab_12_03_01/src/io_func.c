#include <stdio.h>
#include "exit_code.h"
#include "io_func.h"

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
