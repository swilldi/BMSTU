#include "out_func.h"

void print_err_msg(error rc)
{
    if (rc == OK)
        return;

    switch (rc)
    {
        case INVALID_ARGS_COUNT:
            printf("Мало аргументов");
            break;
        case INVALID_ACTION:
            printf("Некоректное действие");
            break;
        case FILE_OPEN_ERR:
            printf("Ошибка выделения памяти");
            break;
        case EMPTY_FILE:
            printf("Пустой файл");
            break;
        case INVALID_DATA:
            printf("Некоректные данные в файле");
            break;
        case MEMORY_ERR:
            printf("Ошибка выделения памяти");
            break;
        default:
            printf("Неизвестная ошибка");
            break;
    }
}

void print_int(void *value)
{
    int *num = value;
    printf("%d\n", *num);
}

void print_prime_num(void *value)
{
    int *num = value;
    printf("%d ", *num);
}
