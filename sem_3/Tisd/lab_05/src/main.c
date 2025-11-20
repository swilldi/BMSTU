#include <stdio.h>
#include <stdbool.h>

#include "exit_code.h"
#include "io_func.h"
#include "enums.h"
#include "test.h"

#include "process_device.h"


// TODO Выбор типа данных для очереди
// TODO Выбор симуляция очереди

void print_prog_mode_list(void)
{
    printf(
        "РЕЖИМ ПРОГРАММЫ:\n"
        "--------------------------------\n"
        "1. Очередь на списке\n"
        "2. Обслуживающий аппарат\n"
        "3. Выполнить сравнение\n"
        "0. Выход\n"
        "--------------------------------\n"
    );
}

void print_queue_mode_list(void)
{
    printf(
        "\nТИП ДАННЫХ ОЧЕРЕДИ:\n"
        "-----------------------------------------------------\n"
        "1. Статический массив\n"
        "2. Список\n"
        "0. Выход\n"
        "-----------------------------------------------------\n"
    );
}


int input_trange(trange_t *tr)
{
    int rc;
    q_type tmp;
    rc = input_value(&tmp);
    if (rc != OK)
    {
        return rc;
    }
    if (tmp < 0)
    {
        return INVALID_INPUT;
    }
    tr->min = tmp;

    rc = input_value(&tmp);
    if (rc != OK)
    {
        return rc;
    }
    if (tmp < tr->min)
    {
        return INVALID_RANGE;
    }
    else if (tmp < 0)
    {
        return INVALID_INPUT;
    }
    tr->max = tmp;

    return OK; 

}

int main(void) 
{
    int rc = OK;
    int cmd = NO_CMD;
    q_type tmp_value;
    
    

    // TODO Выбор режима работы
    #ifndef FUNC_OUT
    print_prog_mode_list();
    #endif
    
    #ifndef FUNC_OUT
    printf("Введите номер: ");
    #endif
    rc = input_cmd(&cmd, MAX_PROGRAMM_MODE);
    if (rc != OK)
    {
        print_err_msg(rc);
        return rc;
    }
    #ifndef FUNC_OUT
    printf("--------------------------------\n");
    #endif

    if (cmd == COMPARE)
    {
        rc = run_compare_tests();
        print_err_msg(rc);
        return rc;
    }
    else if (cmd == PROCESS_DEVICE)
    {
        trange_t arr_t1, t1, arr_t2, t2;
        queue_mode_t mode;
        int request_count = 1000;
        // int request_count = 100;

        #ifndef FUNC_OUT
        print_queue_mode_list();
        printf("Введите номер: ");
        #endif

        rc = input_cmd(&cmd, MAX_QUEUE_MODE);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        #ifndef FUNC_OUT
        printf("-----------------------------------------------------\n");
        #endif

        if (cmd == EXIT)
            return rc;
        
        mode = cmd;
        
        // Завки I-го типа
        #ifndef FUNC_OUT
        printf(
            "\nВВОД ДАННЫХ ОБ ДИАПАЗОНАХ ЗАЯВОК\n"
            "значение в скобках – значения по заданию\n"
            "Сначение вводятся в формате \"min max\"\n"
            "min – нижняя граница диапазона\n"
            "max – верхняя граница диапазона\n"
            "----------------------------------\n"
            "-- Заявки I-го типа -- \n"
            "Диапазон прихода (1 5): "
        );
        #endif
        rc = input_trange(&arr_t1);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        #ifndef FUNC_OUT
        printf("Диапазон выполнения (0 4): ");
        #endif
        rc = input_trange(&t1);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        
        // Завки II-го типа
        #ifndef FUNC_OUT
        printf(
            "----------------------------------\n"
            "-- Заявки II-го типа -- \n"
            "Диапазон прихода (0 3): "
        );
        #endif
        rc = input_trange(&arr_t2);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        #ifndef FUNC_OUT
        printf("Диапазон выполнения (0 1): ");
        #endif 
        rc = input_trange(&t2);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        #ifndef FUNC_OUT
        printf("----------------------------------\n\n");
        #endif

        // rc = run_process_divece(mode, request_count, &arr_t1, &t1, &arr_t2, &t2);
        rc = run_process_divece(mode, request_count, &arr_t1, &t1, &arr_t2, &t2);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
    }
    else if (cmd == EMULATE_LIST_QUEUE)
    {
        // Эмуляция очереди на списке
        #ifndef FUNC_OUT
        print_queue_cmd_list();
        #endif
        queue_list_t *queue = create_queue_list();
        while (rc == OK && cmd != EXIT)
        {
            #ifndef FUNC_OUT
            printf("Введите номер: ");
            #endif
            
            rc = input_cmd(&cmd, MAX_CMD_ACTION);
            if (rc != OK)
                cmd = CONTINUE;

            switch (cmd)
            {
                case CONTINUE:
                case EXIT:
                    break;
                case PUSH:
                    // TODO переполнение
                    // if (is_full(queue))
                    // {
                    //     rc = QUEUE_OVERFLOW;
                    //     break;
                    // }

                    #ifndef FUNC_OUT
                    printf("Введите число: ");
                    #endif

                    rc = input_value(&tmp_value);
                    if (rc != OK)
                        break;
                    rc = push_list(queue, tmp_value);
                    #ifndef FUNC_OUT
                    printf("-----------------------------\n");
                    #endif
                    break;
                case POP:
                    if (is_empty_q_list(queue))
                    {
                        rc = QUEUE_IS_EMPTY;
                        break;
                    }
                    
                    node_t *ptmp = get_piout_queue_list(queue);
                    (void)ptmp;
                    rc = pop_list(queue, &tmp_value);
                
                    #ifndef FUNC_OUT
                    if (rc == OK)
                    {
                        printf("Удален: %.2lf (%p)\n", tmp_value, (void*)ptmp);
                    }
                    printf("-----------------------------\n");
                    #endif
                    break;
                case PRINT_VALUE:
                    print_queue_list_info(queue);
                    #ifndef FUNC_OUT
                    printf("-----------------------------\n");
                    #endif
                    break;
                default:
                    rc = INVALID_CMD_RANGE;
                    break;
            }

            if (rc != OK)
            {
                print_err_msg(rc);
                #ifndef FUNC_OUT
                printf("-----------------------------\n");
                #endif
                rc = OK;
            }
        }

        destroy_queue_list(queue);
    }

    
}

