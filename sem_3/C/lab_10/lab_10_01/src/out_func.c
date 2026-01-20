#include "out_func.h"
#include "item.h"

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
        case EMPTY_LIST:
            printf("Пустой список");
            break;
        case INVALID_INPUT:
            printf("Некоректный ввод");
            break;
        case INVALID_INDEX:
            printf("Некоректный индекс");
            break;
        case EMPTY_STR:
            printf("Пустая строка");
            break;
        default:
            printf("Неизвестная ошибка");
            break;
    }
    printf("\n");
}

void print_int(void *value)
{
    int *num = value;
    printf("%d\n", *num);
}

void print_item(void *value)
{
    item_t *item = value;
    printf("| %16s | %10d | %10.2f |\n", item->title, item->prise, item->weight);
}

void print_item_clear(void *value)
{
    item_t *item = value;
    printf("%s\n%d\n%.2f\n", item->title, item->prise, item->weight);
}
