#include "stack_type.h"
#include "stack_func.h"
#include "stack_list_func.h"
#include <stdio.h>
#include "io_func.h"
#include <stdio.h>
#include "exit_code.h"
#include "test.h"



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
                    if (is_full(&stack))
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
                    rc = push(&stack, buff);
                    break;
                case REMOVE:
                    rc = pop(&stack, buff);
                
                    #ifndef FUNC_OUT
                    if (rc == OK)
                        printf("Удален: %s\n", buff);
                    #endif
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
                    if (node_count == 0)
                    {
                        rc = STACK_IS_EMPTY;
                        break;
                    }
                    rc = add_elem_to_history_arr(history_arr, stack_l);
                    if (rc != OK)
                        break;
                    
                    node_count -= 1;
                    
                    rc = pop_l(&stack_l, buff);
                    #ifndef FUNC_OUT
                    if (rc == OK)
                        printf("Удален: %s\n", buff);
                    #endif

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

        if (rc != OK)
        {
            print_err_msg(rc);
            rc = OK;
        }
    }

    return rc;
}
