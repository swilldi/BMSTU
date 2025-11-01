#include "stack_type.h"
#include "stack_func.h"
#include "stack_list_func.h"
#include <stdio.h>
#include "io_func.h"
#include <stdio.h>
#include "exit_code.h"
#include "test.h"

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
        case OK:
            break;
        default:
            printf("Неизвестная ошибка\n");
            break;
    }
}

typedef enum
{
    STACK_EMULATE = 1,
    COMPARE,

    MAX_WORK_MOD
} work_mode_t;

typedef enum
{
    STATIC_STACK = 1,
    LIST_STACK,

    MAX_TYPE_STACK
} type_stack;

typedef enum
{
    EXIT,
    ADD,
    REMOVE,
    ACTION,
    SHOW_CONTENT,
    SHOW_CONTENT_ADDRESS,
    SHOW_HISTORY,

    MAX_COMMAND_T
} command_t;

error input_cmd(int *cmd, int upper_limit)
{
    if (scanf("%d", cmd) != 1)
        return INPUT_ERR;
    
    if (*cmd >= upper_limit || *cmd < 0)
        return CMD_RANGE_ERR;

    while (getchar() != '\n');

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

#include "stdbool.h"
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

int main(void)
{
    int rc = OK;
    int cmd = SHOW_CONTENT;

    char data[STACK_MAX_LEN][STR_MAX_LEN];
    my_stack_t stack = { .down_p = data, .sp = data - 1};
    size_t node_count = 0;
    
    stack_list_t *stack_l = NULL;
    del_history_arr *history_arr;

    // Ввод режима работы
    #ifndef FUNC_OUT
    print_work_mode_info();
    printf("Введите номер: ");
    #endif
    work_mode_t work_mode;
    rc = input_cmd((int*)&work_mode, MAX_TYPE_STACK);
    if (rc != OK)
    {
        print_err_msg(rc);
        return rc;
    }

    switch ((int)work_mode)
    {
        case STACK_EMULATE:
            #ifndef FUNC_OUT
            printf("Эмуляция стека\n");
            #endif
            break;
        case COMPARE:
            #ifndef  FUNC_OUT
            printf("Выполнение сравнения\n");
            #endif
            rc = run_tests();
            return rc;
            break;
        case EXIT:
            return rc;
    }

    // ввод типа стека
    #ifndef FUNC_OUT
    print_type_stack_info();
    printf("Введите номер: ");
    #endif
    type_stack stack_mode;
    rc = input_cmd((int*)&stack_mode, MAX_TYPE_STACK);
    if (rc != OK || stack_mode <= 0)
    {
        print_err_msg(rc);
        return rc;
    }

    if (stack_mode == LIST_STACK)
    {
        history_arr = create_del_history_arr();
        if (!history_arr)
        {
            rc = MEMORY_ERR;
            print_err_msg(rc);
            return rc;
        }
    }

    #ifndef FUNC_OUT
    print_cmd_list();
    #endif

    char buff[STR_MAX_LEN];
    while (rc == OK && cmd != EXIT)
    {
        #ifndef FUNC_OUT
        printf("Введите номер: ");
        #endif
        
        rc = input_cmd(&cmd, MAX_COMMAND_T);

        // #ifndef FUNC_OUT
        // printf("\n");
        // #endif

        if (stack_mode == STATIC_STACK)
        {
            switch (cmd)
            {
                case EXIT:
                    break;
                case ADD:
                    #ifndef FUNC_OUT
                    printf("Введите строку: ");
                    #endif

                    rc = input_str(buff, stdin);
                    if (rc != OK)
                        break;
                    rc = push(&stack, buff);
                    break;
                case REMOVE:
                    rc = pop(&stack, buff);
                    break;
                case ACTION:
                    print_rev_str(&stack);
                    break;
                case SHOW_CONTENT:
                    rc = print_all_stack(&stack);
                    break;
                case SHOW_HISTORY:
                case SHOW_CONTENT_ADDRESS:
                    printf("Команда доступна только для стека основанного на списке\n");
                    break;
                default:
                    rc = CMD_RANGE_ERR;
                    break;
            }
        }
        else if (stack_mode == LIST_STACK)
        {
            
            
            switch (cmd)
            {
                case EXIT:
                    free_stack_list(stack_l);
                    free_history_arr(history_arr);
                    break;
                case ADD:
                    if (node_count == STACK_MAX_LEN)
                    {
                        rc = STACK_OVERFLOW;
                        break;
                    }
                    #ifndef FUNC_OUT
                    printf("Введите строку: ");
                    #endif
                    rc = input_str(buff, stdin);
                    if (rc != OK)
                        break;

                    rc = push_l(&stack_l, buff);
                    node_count += 1;
                    break;
                case REMOVE:
                    rc = add_elem_to_history_arr(history_arr, stack_l);
                    if (rc != OK)
                        break;

                    rc = pop_l(&stack_l, buff);
                    break;
                case ACTION:
                    print_rev_str_l(&stack_l);
                    break;
                case SHOW_CONTENT:
                    rc = print_all_stack_list(stack_l);
                    break;
                case SHOW_CONTENT_ADDRESS:
                    rc = print_all_stack_list_address(stack_l);
                    break;
                case SHOW_HISTORY:
                    rc = print_history_arr(history_arr);
                    break;
                default:
                    rc = CMD_RANGE_ERR;
                    break;
            }
        }
        
        if (rc == HISTORY_IS_EMPTY)
        {
            rc = OK;
            printf("История удаления пуста\n");
        }
        else if (rc == STACK_IS_EMPTY)
        {
            rc = OK;
            printf("Стек пустой\n");
        }
        else if (rc == STACK_OVERFLOW)
        {
            rc = OK;
            printf("Стек переполнен\n");
        }
    }

    print_err_msg(rc);
    return rc;
}

// int main(void)
// {
//     stack_list_t *s = NULL;
//     push_l(&s, "123");
//     push_l(&s, "123");
//     push_l(&s, "123");
//     char v[128];
//     pop_l(&s, v);
//     pop_l(&s, v);
//     pop_l(&s, v);

//     free_stack_list(s);
// }
