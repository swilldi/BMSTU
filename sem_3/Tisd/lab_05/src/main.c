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
        "Выберите режим работы программы:\n"
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
        "\nВыберите на каком типе данных будет работать очередь:\n"
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
    print_prog_mode_list();
    
    printf("Введите номер: ");
    rc = input_cmd(&cmd, MAX_PROGRAMM_MODE);
    if (rc != OK)
    {
        print_err_msg(rc);
        return rc;
    }
    printf("--------------------------------\n");

    if (cmd == COMPARE)
    {
        rc = run_compare_tests();
        print_err_msg(rc);
        return rc;
    }
    else if (cmd == PROCESS_DEVICE)
    {
        trange_t t1, t2, t3, t4;
        queue_mode_t mode;
        int request_count = 1000;

        print_queue_mode_list();
        printf("Введите номер: ");

        rc = input_cmd(&cmd, MAX_QUEUE_MODE);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        printf("-----------------------------------------------------\n");

        if (cmd == EXIT)
            return rc;
        
        mode = cmd;
        
        // Завки I-го типа
        printf(
            "-----------------------------------------------------\n"
            "ЗАЯВКА I-ГО ТИПА: \n"
            "Диапазон прихода: "
        );
        rc = input_trange(&t1);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        printf("Диапазон выполнения: ");
        rc = input_trange(&t3);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        
        // Завки II-го типа
        printf(
            "-----------------------------------------------------\n"
            "ЗАЯВКА II-ГО ТИПА: \n"
            "Диапазон прихода: "
        );
        rc = input_trange(&t2);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        printf("Диапазон выполнения: ");
        rc = input_trange(&t4);
        if (rc != OK)
        {
            print_err_msg(rc);
            return rc;
        }
        printf("-----------------------------------------------------\n\n");

        rc = run_process_divece(mode, request_count, &t1, &t2, &t3, &t4);
    }
    else if (cmd == EMULATE_LIST_QUEUE)
    {
        // Эмуляция очереди на списке
        print_queue_cmd_list();
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
                    printf("-----------------------------\n");
                    break;
                case POP:
                    
                    rc = pop_list(queue, &tmp_value);
                
                    #ifndef FUNC_OUT
                    if (rc == OK)
                        printf("Удален: %.2lf\n", tmp_value);
                    #endif
                    printf("-----------------------------\n");
                    break;
                case PRINT_VALUE:
                    print_queue_list_info(queue);
                    printf("-----------------------------\n");
                    break;
                default:
                    rc = INVALID_CMD_RANGE;
                    break;
            }

            if (rc != OK)
            {
                print_err_msg(rc);
                rc = OK;
            }
        }

        destroy_queue_list(queue);
    }

    
}

