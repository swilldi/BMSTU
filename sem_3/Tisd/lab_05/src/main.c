#include <stdio.h>
#include <stdbool.h>

#include "exit_code.h"
#include "io_func.h"
#include "enums.h"
#include "queue_array_func.h"
#include "queue_list_func.h"
#include "io_func.h"



#include <time.h>

#define REQUEST_COUNT 1000
#define EPS 1e-5
#include <math.h>

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


error push(queue_t *queue, q_type value)
{
    if (queue->mode == ARRAY)
        return push_array(queue->data.arr, value);
    else if (queue->mode == LIST)
        return push_list(queue->data.list, value);
    else
        // TODO Придумать ощибку
        return 1;
}

error pop(queue_t *queue, q_type *value)
{
    if (queue->mode == ARRAY)
        return pop_array(queue->data.arr, value);
    else if (queue->mode == LIST)
        return pop_list(queue->data.list, value);
    else
        // TODO Придумать ощибку
        return 1;
}

error is_empty_q(queue_t *queue)
{
    if (queue->mode == ARRAY)
        return is_empty_q_arr(queue->data.arr);
    else if (queue->mode == LIST)
        return is_empty_q_list(queue->data.list);
    else
        // TODO Придумать ощибку
        return 1;
}


queue_t *create_queue(queue_mode_t mode)
{

    queue_t *queue = malloc(sizeof(queue_t));
    if (!queue)
        return NULL;

    queue->mode = mode;

    if (mode == ARRAY)
    {
        queue->data.arr = create_queue_array();
        if (!queue->data.arr)
            return NULL;
    }
    else if (mode == LIST)
    {
        queue->data.list = create_queue_list();
        if (!queue->data.list)
            return NULL;
    }
    else
    {
        return NULL;
    }

    return queue;
}

typedef enum 
{
    WORK_T1,
    WORK_T2,
    WORK_END,
    FREE
} device_action_t;

double rand_uniform(double min, double max) {
    return min + (max - min) * ((double) rand() / RAND_MAX);
}

q_type min(q_type a, q_type b)
{
    return a < b ? a : b;
}

int main(void) {
    srand(time(NULL));

    int rc;

    queue_mode_t mode = LIST;
    queue_t *q1 = create_queue(mode);
    queue_t *q2 = create_queue(mode);


    double t1_min = 1.0, t1_max = 5.0;  // Приход в очередь I
    double t2_min = 0.0, t2_max = 3.0;  // Приход в очередь II
    double t3_min = 0.0, t3_max = 4.0;  // Диапазон времени в I
    double t4_min = 0.0, t4_max = 1.0;  // Диапазон времени в II

    int in_t1 = 0;
    int out_t1 = 0;
    int in_t2 = 0;
    int out_t2 = 0;


    // double cur_time = 0.0;
    double next_arrive_1 = rand_uniform(t1_min, t1_max);
    double next_arrive_2 = rand_uniform(t2_min, t2_max);
    double end_time = next_arrive_1 + next_arrive_2; 


    device_action_t device_status = FREE;

    size_t processed_count = 0;
    q_type free_time = 0;
    q_type t;

    q_type next_time_point = 0.0;
    device_action_t next_action = FREE;

    while (out_t1 < REQUEST_COUNT) {
        // printf("%zu\n", processed_count);
        // Поиск ближайшего события
        
        
        if (next_arrive_1 < next_arrive_2 && next_arrive_1 < end_time)
        {
            next_time_point = next_arrive_1;
            next_action = WORK_T1;
        }
        else if (next_arrive_2 < next_arrive_1 && next_arrive_2 < end_time)
        {
            next_time_point = next_arrive_2;
            next_action = WORK_T2;
        }
        else if (end_time < next_arrive_1 && end_time < next_arrive_2)
        {
            next_time_point = end_time;
            next_action = WORK_END;
        }
        
        t = next_time_point;

        
        if (next_action == WORK_T1) {
            // Поступила заявка 1-го типа
            // TODO обрабатывается заяка 2-го типа
            if (device_status == WORK_T2)
            {
                // удаляем из очереди недообработанный процесс
                q_type tmp_time;
                rc = pop(q2, &tmp_time);

                // добавляем в конец остаток
                rc = push(q2, end_time - t);
                device_status = FREE;
            }
            
            rc = push(q1, rand_uniform(t3_min, t3_max));
            next_arrive_1 = t + rand_uniform(t1_min, t1_max);
            // printf("t=%.2f: Поступила заявка 1\n", t);
        } else if (next_action == WORK_T2) {
            // Поступила заявка 2-го типа
            rc = push(q2, rand_uniform(t4_min, t4_max));
            next_arrive_2 = t + rand_uniform(t2_min, t2_max);
            // printf("t=%.2f: Поступила заявка 2\n", t);
        } else if (next_action == WORK_END) {
            // Завершение обслуживания
            processed_count += 1;
            device_status = FREE;
        }

        // Если никто не обслуживается — взять с головы очереди
        if (device_status == FREE) {
            if (!is_empty_q(q1)) {
                device_status = WORK_T1;
                
                q_type work_time;
                rc = pop(q1, &work_time);

                end_time = t + work_time;
                // printf("t=%.2f: Начато обслуживание заявки 1\n", t);
            } else if (!is_empty_q(q2)) {
                device_status = WORK_T2;
                
                q_type work_time;
                rc = pop(q2, &work_time);

                end_time = t + work_time;
                // printf("t=%.2f: Начато обслуживание заявки 2\n", t);
            }
            else
            {
                end_time = next_arrive_1 + next_arrive_2;
                free_time += min(next_arrive_1, next_arrive_2) - t;
            }
        }
    }

    printf("t = %f\n", t);
    printf("free_time = %f\n", free_time);
    printf("rc = %d\n", rc);
    return 0;
}


/*
2 может войти если нет в процессе 1

Если работает 2-я и в пустую очередь приходит 1, то
- обработка останавливается
- процесс уходит в конец очереди
- прищедщая заявка начинает выполняться
*/

