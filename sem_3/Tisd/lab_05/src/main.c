#include <stdio.h>
#include <stdbool.h>

#include "exit_code.h"
#include "io_func.h"
#include "enums.h"
#include "queue_array_func.h"
#include "queue_list_func.h"
#include "io_func.h"



int main(void)
{
    error rc = OK;
    int cmd = NO_CMD;
    

    union
    {
        queue_array_t *arr;
        queue_list_t *list;
    } queue;

    // void *ptr = queue.arr;
    // ptr = create_queue_array();
    
    void *ptr = queue.list;
    ptr = create_queue_list();

    q_type value_tmp;

    print_cmd_list();
    // while (cmd != EXIT)
    // {
    //     printf("Введите команду: ");
    //     rc = input_cmd(&cmd);
    //     if (rc != OK)
    //         cmd = CONTINUE;
    
    //     switch (cmd)
    //     {
    //         case PUSH:
    //             rc = input_value(&value_tmp);
    //             if (rc != OK)
    //                 break;

    //             rc = push_array(ptr, value_tmp); 
    //             break;
    //         case POP:
    //             rc = pop_array(ptr, &value_tmp);
    //             printf("rc: %d\n", rc);
    //             break;
    //         case PRINT_VALUE:
    //             if (is_empty_q_arr(ptr))
    //             {
    //                 rc = QUEUE_IS_EMPTY;
    //                 break;
    //             }
    //             print_queue_array(ptr);
    //             break;
    //         case PRINT_ALL:
    //             print_queue_array_full(ptr);
    //             break;
    //         case EXIT:
    //         case CONTINUE:
    //             break;
    //     }
    //     if (rc != OK)
    //     {
    //         print_err_msg(rc);
    //         rc = OK;
    //     }
    // }


    while (cmd != EXIT)
    {
        printf("Введите команду: ");
        rc = input_cmd(&cmd);
        if (rc != OK)
            cmd = CONTINUE;
    
        switch (cmd)
        {
            case PUSH:
                rc = input_value(&value_tmp);
                if (rc != OK)
                    break;

                rc = push_list(ptr, value_tmp); 
                break;
            case POP:
                rc = pop_list(ptr, &value_tmp);
                printf("rc: %d\n", rc);
                break;
            case PRINT_VALUE:
                print_queue_list(ptr);
                break;
            case PRINT_ALL:
                print_queue_list_info(ptr);
                break;
            case EXIT:
            case CONTINUE:
                break;
        }
        if (rc != OK)
        {
            print_err_msg(rc);
            rc = OK;
        }
    }
}
