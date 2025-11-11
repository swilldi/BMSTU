#include <stdio.h>
#include <stdbool.h>

#include "exit_code.h"
#include "io_func.h"
#include "enums.h"
#include "queue_array_func.h"
#include "queue_list_func.h"
#include "io_func.h"



// int main(void)
// {
//     error rc = OK;
//     int cmd = NO_CMD;
    

//     union
//     {
//         queue_array_t *arr;
//         queue_list_t *list;
//     } queue;

//     // void *ptr = queue.arr;
//     // ptr = create_queue_array();
    
//     void *ptr = queue.list;
//     ptr = create_queue_list();

//     q_type value_tmp;

//     print_cmd_list();
//     // while (cmd != EXIT)
//     // {
//     //     printf("Введите команду: ");
//     //     rc = input_cmd(&cmd);
//     //     if (rc != OK)
//     //         cmd = CONTINUE;
    
//     //     switch (cmd)
//     //     {
//     //         case PUSH:
//     //             rc = input_value(&value_tmp);
//     //             if (rc != OK)
//     //                 break;

//     //             rc = push_array(ptr, value_tmp); 
//     //             break;
//     //         case POP:
//     //             rc = pop_array(ptr, &value_tmp);
//     //             printf("rc: %d\n", rc);
//     //             break;
//     //         case PRINT_VALUE:
//     //             if (is_empty_q_arr(ptr))
//     //             {
//     //                 rc = QUEUE_IS_EMPTY;
//     //                 break;
//     //             }
//     //             print_queue_array(ptr);
//     //             break;
//     //         case PRINT_ALL:
//     //             print_queue_array_full(ptr);
//     //             break;
//     //         case EXIT:
//     //         case CONTINUE:
//     //             break;
//     //     }
//     //     if (rc != OK)
//     //     {
//     //         print_err_msg(rc);
//     //         rc = OK;
//     //     }
//     // }


//     // while (cmd != EXIT)
//     // {
//     //     printf("Введите команду: ");
//     //     rc = input_cmd(&cmd);
//     //     if (rc != OK)
//     //         cmd = CONTINUE;
    
//     //     switch (cmd)
//     //     {
//     //         case PUSH:
//     //             rc = input_value(&value_tmp);
//     //             if (rc != OK)
//     //                 break;

//     //             rc = push_list(ptr, value_tmp); 
//     //             break;
//     //         case POP:
//     //             rc = pop_list(ptr, &value_tmp);
//     //             printf("rc: %d\n", rc);
//     //             break;
//     //         case PRINT_VALUE:
//     //             print_queue_list(ptr);
//     //             break;
//     //         case PRINT_ALL:
//     //             print_queue_list_info(ptr);
//     //             break;
//     //         case EXIT:
//     //         case CONTINUE:
//     //             break;
//     //     }
//     //     if (rc != OK)
//     //     {
//     //         print_err_msg(rc);
//     //         rc = OK;
//     //     }
//     // }
// }


#include <time.h>

#define REQUEST_COUNT 5
#define EPS 1e-5
#include <math.h>
typedef int interval_t;

bool is_eq_inverval(interval_t a, interval_t b)
{
    return fabs((double)a - b) < EPS;
}

interval_t min_interval(interval_t a, interval_t b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

interval_t *array_arrival_time_generate(interval_t min, interval_t max)
{
    interval_t *arr = malloc(sizeof(interval_t) * REQUEST_COUNT);

    // arr[0] = min + (max - min) * ((interval_t)rand() / RAND_MAX);
    // for (size_t i = 1; i < REQUEST_COUNT; i++)
    //     arr[i] = arr[i - 1] + min + (max - min) * ((interval_t)rand() / RAND_MAX);
    arr[0] = min + rand() % (max - min);
    for (size_t i = 1; i < REQUEST_COUNT; i++)
        arr[i] = arr[i - 1] + min + rand() % (max - min);

    return arr;
}

interval_t *array_processing_time_generate(interval_t min, interval_t max)
{
    interval_t *arr = malloc(sizeof(interval_t) * REQUEST_COUNT);

    // for (size_t i = 0; i < REQUEST_COUNT; i++)
    //     arr[i] = min + (max - min) * ((interval_t)rand() / RAND_MAX);
    for (size_t i = 0; i < REQUEST_COUNT; i++)
        arr[i] = min + rand() % (max - min);

    return arr;
}

void print_arr_interval(interval_t *arr)
{
    for (size_t i = 0; i < REQUEST_COUNT; i++)
        // printf("%8.2f ", arr[i]);
        printf("%8d ", arr[i]);
    printf("\n");
}

int main(void)
{
    long t = time(NULL);
    printf("%ld\n", t);
    // srand(1762775924);
    int rc;

    interval_t *time_arrival_t1 = array_arrival_time_generate(1, 5);
    interval_t *time_processing_t1 = array_processing_time_generate(0, 6);
    
    print_arr_interval(time_arrival_t1);
    print_arr_interval(time_processing_t1);


    queue_list_t *q = create_queue_list();
    size_t i_t1 = 0;
    interval_t cur_time = time_arrival_t1[i_t1];  // текущее время
    interval_t end_time = cur_time;  // время завершение текущего процесса
    interval_t free_time = cur_time;  // время время простоя
    bool is_busy = false;

    while (i_t1 < REQUEST_COUNT)
    {
        // процесс завершился
        cur_time = min_interval(time_arrival_t1[i_t1], end_time);
 
        // Прибывает новый процесс
        if (is_eq_inverval(cur_time, time_arrival_t1[i_t1]))
        {
            // Очередь пустая
            if (is_empty_q_list(q) && !is_busy)
            {
                is_busy = true;
                end_time = cur_time + time_processing_t1[i_t1];
            }
            // Очередь не пустая
            else
            {
                // добавляем процесс в очередь
                rc = push_list(q, time_processing_t1[i_t1]);
            }
            i_t1 += 1;
        }
        // предыдущий процесс завершился
        else if (is_eq_inverval(cur_time, end_time))
        {
            if (is_empty_q_list(q))
            {
                // TODO считать время простоя
                is_busy = false;
                free_time += time_arrival_t1[i_t1] - cur_time;
                cur_time = time_arrival_t1[i_t1];
                end_time = cur_time + time_processing_t1[i_t1];
            }
            else
            {
                interval_t time_to_process;
                rc = pop_list(q, &time_to_process);
                end_time = cur_time + time_to_process;
            }
            // TODO Начать выполнять
            // TODO Добавить в очередь
        }
    }

    cur_time = end_time;

    interval_t time_to_process;
    while (pop_list(q, &time_to_process) != QUEUE_IS_EMPTY)
        cur_time  += time_to_process;
        
        // можно начать новый процесс
        // - очередь пустая
        // - очередь не пустая
        // нельзя добавить новый элемент


    printf("rc = %d\n", rc);
    printf("cur_time = %d\n", cur_time);
    printf("free_time = %d\n", free_time);
    free(q);
    free(time_arrival_t1);
    free(time_processing_t1);
    
}


