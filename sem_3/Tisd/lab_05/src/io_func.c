#include <stdio.h>
#include "io_func.h"
#include "enums.h"


error input_cmd(int *cmd)
{
    char buffer[BUFFER_LEN];
    if (fgets(buffer, BUFFER_LEN, stdin) == NULL)
        return INVALID_INPUT;
    if (sscanf(buffer, "%d", cmd) != 1)
        return INVALID_INPUT;
    
    if (*cmd >= MAX_CMD_ACTION || *cmd < 0)
        return INVALID_CMD_RANGE;

    // очищение буффера stdin
    // int ch = fgetc(stdin);
    // while (ch != '\n' && !feof(stdin))
    //     ch = fgetc(stdin);
    
    return OK; 
}

error input_value(q_type *value)
{
    char buffer[BUFFER_LEN];
    if (fgets(buffer, BUFFER_LEN, stdin) == NULL)
        return INVALID_INPUT;
    if (sscanf(buffer, "%f", value) != 1)
        return INVALID_INPUT;
    
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
        default:
            printf("Неизвествная ошибка");
            break;
    }
    printf("\n");

}

void print_cmd_list(void)
{
    printf(
        "1. Добавить элемент\n"
        "2. Удалить элемент\n"
        "3. Вывести содержимое очереди\n"
        "4. Вывести полное представление очереди\n"
        "0. Выход\n"
    );
}
