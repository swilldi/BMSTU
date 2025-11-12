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

typedef enum
{
    LIST,
    ARRAY
} queue_mode_t;

typedef struct 
{
    union
    {
        queue_array_t *arr;
        queue_list_t *list;
    } data;
    queue_mode_t mode;

} queue_t;

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

typedef enum 
{
    BUSY_T1,
    BUSY_T2,
    FREE
} status_device_t;

void get_process_name(interval_t *arr, interval_t elem)
{
    
}

int main(void)
{
    long t = time(NULL);
    printf("%ld\n", t);
    srand(t);
    srand(1762916959);
    int rc;

    interval_t *time_arrival_t1 = array_arrival_time_generate(1, 5);
    interval_t *time_processing_t1 = array_processing_time_generate(0, 6);
    interval_t *time_arrival_t2 = array_arrival_time_generate(0, 3);
    interval_t *time_processing_t2 = array_processing_time_generate(0, 4);
    
    printf("I-й поток\n");
    printf("Время приход:");
    print_arr_interval(time_arrival_t1);
    printf("Время работы:");
    print_arr_interval(time_processing_t1);
    printf("II-й поток\n");
    printf("Время приход:");
    print_arr_interval(time_arrival_t2);
    printf("Время работы:");
    print_arr_interval(time_processing_t2);


    queue_list_t *q_t1 = create_queue_list();
    queue_list_t *q_t2 = create_queue_list();
    size_t i_t1 = 0, i_t2 = 0;
    
    // текущее время (ближайшее время прихода заявки)
    interval_t cur_time = min_interval(time_arrival_t1[i_t1], time_arrival_t2[i_t2]);;  
    // время завершение текущего процесса
    interval_t end_time = cur_time;
    // время время простоя
    interval_t free_time = cur_time;

    status_device_t status_device = FREE;

    while (i_t1 < REQUEST_COUNT || i_t2 < REQUEST_COUNT)
    {
        // Следующая временная точка
        if (i_t1 >= REQUEST_COUNT)
        {
            cur_time = min_interval(time_arrival_t2[i_t2], end_time);    
        }
        else if (i_t2 >= REQUEST_COUNT)
        {
            cur_time = min_interval(time_arrival_t1[i_t1], end_time);
        }
        else
        {
            cur_time = min_interval(time_arrival_t1[i_t1] ,min_interval(time_arrival_t2[i_t2], end_time));
        }
 
        // Новый процесс t1
        if (i_t1 < REQUEST_COUNT && is_eq_inverval(cur_time, time_arrival_t1[i_t1]))
        {
            // Очередь пустая
            if (is_empty_q_list(q_t1) && status_device == FREE)
            {
                status_device = BUSY_T1;
                end_time = cur_time + time_processing_t1[i_t1];
            }
            // обрабатывается процесс из t_2
            else if (status_device == BUSY_T2)
            {
                // Время прихода заявки i_t2 илил i_t2 - 1 ? 
                interval_t time_to_complete = cur_time - end_time;
                if (time_to_complete)
                {
                    rc = push_list(q_t2, time_to_complete);
                }

                end_time = cur_time + time_processing_t1[i_t1];
                status_device = BUSY_T1;
            }
            // Очередь не пустая
            else
            {
                // добавляем процесс в очередь
                rc = push_list(q_t1, time_processing_t1[i_t1]);
            }
            i_t1 += 1;
        }
        // Новый процесс t2
        else if (i_t2 < REQUEST_COUNT && is_eq_inverval(cur_time, time_arrival_t2[i_t2]))
        {
            // Очередь пустая
            if (is_empty_q_list(q_t2) && status_device == FREE)
            {
                status_device = BUSY_T2;
                end_time = cur_time + time_processing_t2[i_t2];
            }
            // Очередь не пустая
            else
            {
                // добавляем процесс в очередь
                rc = push_list(q_t2, time_processing_t2[i_t2]);
            }
            i_t2 += 1;
        }
        // предыдущий процесс завершился
        else if (is_eq_inverval(cur_time, end_time))
        {
            bool q_t1_empty = is_empty_q_list(q_t1), q_t2_empty = is_empty_q_list(q_t2);
            // Нет заявок на обработку
            if (q_t1_empty && q_t2_empty)
            {
                status_device = FREE;
                interval_t next_time_point = 0, time_proccess = 0;
                if (i_t1 >= REQUEST_COUNT || time_arrival_t1[i_t1] > time_arrival_t2[i_t2])
                {
                    next_time_point = time_arrival_t2[i_t2];
                    time_proccess = time_processing_t2[i_t2];
                    i_t2 += 1;
                }
                else if (i_t2 >= REQUEST_COUNT || time_arrival_t1[i_t1] < time_arrival_t2[i_t2])
                {
                    next_time_point = time_arrival_t1[i_t1];
                    time_proccess = time_processing_t1[i_t1];
                    i_t1 += 1;
                }

                free_time += next_time_point - cur_time;
                cur_time = next_time_point;
                end_time = cur_time + time_proccess;
            }
            else
            {
                interval_t time_to_process;
                if (q_t1_empty)
                {
                    rc = pop_list(q_t2, &time_to_process);
                }
                else
                {
                    rc = pop_list(q_t1, &time_to_process);
                }
                
                end_time = cur_time + time_to_process;
            }
        }
    }

    cur_time = end_time;

    interval_t time_to_process;
    // осовбождение очереди I-го типа
    while (pop_list(q_t1, &time_to_process) != QUEUE_IS_EMPTY)
        cur_time  += time_to_process;
    // осовбождение очереди II-го типа 
    while (pop_list(q_t2, &time_to_process) != QUEUE_IS_EMPTY)
        cur_time  += time_to_process;
        
        // можно начать новый процесс
        // - очередь пустая
        // - очередь не пустая
        // нельзя добавить новый элемент


    printf("rc = %d\n", rc);
    printf("cur_time = %d\n", cur_time);
    printf("free_time = %d\n", free_time);
    free(q_t1);
    free(q_t2);
    free(time_arrival_t1);
    free(time_processing_t1);
    
}


/*
2 может войти если нет в процессе 1

Если работает 2-я и в пустую очередь приходит 1, то
- обработка останавливается
- процесс уходит в конец очереди
- прищедщая заявка начинает выполняться
*/

