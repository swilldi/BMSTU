#include <stdio.h>
#include "io_func.h"
#include "enums.h"


error input_cmd(int *cmd, int max_value)
{
    long tmp_cmd;
    if (scanf("%ld", &tmp_cmd) != 1)
    {
        while (getchar() != '\n');
        return INVALID_INPUT;
    }
    
    if (tmp_cmd >= max_value || tmp_cmd < 0)
        return INVALID_CMD_RANGE;

    *cmd = tmp_cmd;

    // очищение буффера stdin
    // int ch = fgetc(stdin);
    // while (ch != '\n' && !feof(stdin))
    //     ch = fgetc(stdin);

    
    return OK; 
}

error input_value(q_type *value)
{
    if (scanf("%f", value) != 1)
    {
        while (getchar() != '\n');
        return INVALID_INPUT;
    }
    
    return OK; 
}

void print_err_msg(error rc)
{
    if (rc == OK)
        return;

    switch (rc)
    {
        case QUEUE_IS_EMPTY:
            printf("Очередь пустая");
            break;
        case QUEUE_OVERFLOW:
            printf("Очередь полная");
            break;
        case INVALID_INPUT:
            printf("Некоректный ввод");
            break;
        case INVALID_CMD_RANGE:
            printf("Введенный номер команды вне диапазона");
            break;
        case INVALID_RANGE:
            printf("Минимальное значение больше максимального");
            break;
        default:
            printf("Неизвествная ошибка");
            break;
    }
    printf("\n");

}

void print_queue_cmd_list(void)
{
    printf(
        "\nВыберите действие:\n"
        "-----------------------------\n"
        "1. Добавить элемент\n"
        "2. Удалить элемент\n"
        "3. Вывести содержимое очереди\n"
        "0. Выход\n"
        "-----------------------------\n"
    );
}
