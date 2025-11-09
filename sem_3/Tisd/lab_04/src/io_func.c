#include "stdio.h"
#include "io_func.h"
#include <string.h>
#include "exit_code.h"
#include "stdbool.h"


error input_str(str_t str, FILE *f)
{
    
    char buff[STR_MAX_LEN + 2];
    if (!fgets(buff, sizeof(buff), f))
        return INPUT_ERR;
    
    size_t len = strlen(buff);
    if (len && buff[len - 1] == '\n')
    {
        len -= 1;
        buff[len] = '\0';
    }

    if (!len)
        return STR_IS_EMPTY;
    else if (len >= STR_MAX_LEN)
        return STR_OVERFLOW;

    strcpy(str, buff);
    
    return OK;
}

void print_work_mode_info(void)
{
    printf(
        "Выберите режим работы программы\n"
        "1. Эмуляция стека\n"
        "2. Выполнить равнение стеков основанных на:\n"
        "       - Статическом массиве\n"
        "       - Односвязном списке\n"
        "0. Выйти\n"
    );
}

void print_type_stack_info(void)
{
    printf(
        "\nВыберите тип данных, на которых будет основана работа стека\n"
        "1. Статический массив\n"
        "2. Односвязный список\n"
        "0. Выйти\n"
    );
}

void print_cmd_list(void)
{
    printf(
        "\nВыберите действие\n"
        "1. Добавить элемент\n"
        "2. Удалить элемент\n"
        "3. Развернутые строки в обратном порядке\n"
        "4. Посмотреть содержимое стека\n"
        "5. Посмотреть содержимое стека c адресами (только для списка)\n"
        "6. Посмотреть истрию удалений  (только для списка)\n"
        "0. Выйти\n"
    );
}

error input_cmd(int *cmd, int upper_limit)
{
    if (scanf("%d", cmd) != 1)
        return INPUT_ERR;
    
    if (*cmd >= upper_limit || *cmd < 0)
        return CMD_RANGE_ERR;

    while (getchar() != '\n');

    return OK;
}

void print_err_msg(error code)
{
    switch (code)
    {
        case STACK_OVERFLOW:
            printf("Стек переполнен\n");
            break;
        case STACK_IS_EMPTY:
            printf("Стек пустой\n");
            break;
        case INPUT_ERR:
            printf("Ошибка ввода\n");
            break;
        case STR_IS_EMPTY:
            printf("Строка пустая\n");
            break;
        case STR_OVERFLOW:
            printf("Слишком длинная строка\n");
            break;
        case MEMORY_ERR:
            printf("Ошибка выделения памяти\n");
            break;
        case CMD_RANGE_ERR:
            printf("Номер команды не в диапазоне\n");
            break;
        case HISTORY_IS_EMPTY:
            printf("История удалений пуста\n");
        case OK:
            break;
        default:
            printf("Неизвестная ошибка\n");
            break;
    }
}

