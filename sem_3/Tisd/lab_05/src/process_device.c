#include <stdio.h>
#include <time.h>
#include <math.h>

#include "queue.h"
#include "process_device.h"

#define SEPARATOR_LINE      "-----------------------------\n"
#define BOLD_SEPARATOR_LINE "|||||||||||||||||||||||||||||\n"


q_type rand_uniform(double min, double max) {
    return (q_type)(min + (max - min) * ((double)rand() / RAND_MAX));
}

q_type min(q_type a, q_type b)
{
    return a < b ? a : b;
}

int run_process_divece(queue_mode_t mode, int request_count, trange_t *arr_t1, trange_t *t1, trange_t *arr_t2, trange_t *t2)
{
    time_t seed  = time(NULL);
    // printf("seed = %ld\n", seed);
    srand(seed);

    int rc;

    // Создание двух очередй
    queue_t *q1 = create_queue(mode);
    if (!q1)
    {
        return MEM_ERR;
    }
    queue_t *q2 = create_queue(mode);
    if (!q2)
    {
        destroy_queue(q1);
        return MEM_ERR;
    }
    queue_t *q1_time = create_queue(mode);
    if (!q1_time)
    {
        destroy_queue(q1);
        destroy_queue(q2);
        return MEM_ERR;
    }
    queue_t *q2_time = create_queue(mode);
    if (!q2_time)
    {
        destroy_queue(q1);
        destroy_queue(q2);
        destroy_queue(q1_time);
        return MEM_ERR;
    }


    // double t1_min = 1.0, t1_max = 5.0;  // Приход в очередь I
    // double t2_min = 0.0, t2_max = 3.0;  // Приход в очередь II
    // double t3_min = 0.0, t3_max = 4.0;  // Диапазон времени в I
    // double t4_min = 0.0, t4_max = 1.0;  // Диапазон времени в II

    // количество вошедших и вышедших в ОА заявок I-го типа
    int in_t1 = 0;
    int out_t1 = 0;
    
    // количество вошедших и вышедших в ОА заявок II-го типа
    int in_t2 = 0;
    int out_t2 = 0;
    // количество выброшенных заявок II-го типа 
    int drop_t2 = 0;

    // Средние значения
    // double avg_time_in_queue = 0;
    double avg_len_q1 = 0;
    double avg_len_q2 = 0;

    double avg_time_q1 = 0;
    double avg_time_q2 = 0;


    // Время прибытия следующих заявок I и II-го типов
    q_type next_arrive_1 = rand_uniform(arr_t1->min, arr_t1->max);
    q_type next_arrive_2 = rand_uniform(arr_t2->min, arr_t2->max);
    // Время завершения текущего процесса
    q_type end_time = INFINITY; 

    // Статус ОА
    device_action_t device_status = FREE;

    // Количество выполненных заяок
    int processed_count = 0;
    // Время простоя
    double free_time = 0;
    // Текущее время
    q_type t = 0;


    // Следующая временная точка
    q_type next_time_point = 0.0;
    q_type last_event_time = 0.0;
    // Следующее действие
    device_action_t next_action = FREE;


    int last_printed_count = 0;
    while (out_t1 < request_count) {
        if (out_t1 % 100 == 0 && out_t1 != last_printed_count)
        {
            last_printed_count = out_t1;
            // текущей и средней длине каждой очереди и о среднем времени пребывания заявок
            // каждого типа в очереди
            
            printf(
                SEPARATOR_LINE
                "КОЛИЧЕСТВО ЗАЯВОК: %d\n"
                SEPARATOR_LINE
                "СРЕДНЯЯ ДЛИНА ОЧЕРЕДИ\n" 
                SEPARATOR_LINE
                "I-й тип: %.0lf\n"
                "II-й тип: %.0lf\n"
                SEPARATOR_LINE
                "ДЛИНА ОЧЕРЕДЕЙ\n"
                SEPARATOR_LINE
                "I-й тип: %d\n"
                "II-й тип: %d\n"
                SEPARATOR_LINE
                "\n",
                out_t1, 
                ceil(avg_len_q1 / t), ceil(avg_len_q2 / t), 
                len_q(q1), len_q(q2)
            );
        }

        // Выбор следующей временной точки
        if (next_arrive_1 <= next_arrive_2 && next_arrive_1 <= end_time)
        {
            next_time_point = next_arrive_1;
            next_action = WORK_T1;
        }
        else if (next_arrive_2 <= next_arrive_1 && next_arrive_2 <= end_time)
        {
            next_time_point = next_arrive_2;
            next_action = WORK_T2;
        }
        else if (end_time <= next_arrive_1 && end_time <= next_arrive_2)
        // else if (end_time < next_arrive_1 && end_time < next_arrive_2)
        {
            next_time_point = end_time;
            next_action = WORK_END;
        }

        
        // Выполнение действия
        last_event_time = t;  
        t = next_time_point;

        if (device_status == FREE)
        {
            free_time += t - last_event_time;
        }
        
        avg_len_q1 += len_q(q1) * (t - last_event_time);
        avg_len_q2 += len_q(q2) * (t - last_event_time);
        

        if (next_action == WORK_T1) 
        {
            // Добавление процесса I

            // В работе процесс II
            if (device_status == WORK_T2 && !is_empty_q(q2))
            {
                push(q2_time, t);

                drop_t2 += 1;

                q_type tmp_time;
                rc = pop(q2, &tmp_time);
                if (rc != OK)
                {
                    break;
                }
                rc = push(q2, end_time - t);
                if (rc != OK)
                {
                    break;
                }
                // rc = push(q2, tmp_time);
                device_status = FREE;
            }
            
            push(q1_time, t);

            rc = push(q1, rand_uniform(t1->min, t1->max));
            if (rc != OK)
            {
                break;
            }
            next_arrive_1 = t + rand_uniform(arr_t1->min, arr_t1->max);
        } 
        else if (next_action == WORK_T2) 
        {
            // Добавление процесса II
            push(q2_time, t);
            rc = push(q2, rand_uniform(t2->min, t2->max));
            if (rc != OK)
            {
                break;
            }

            next_arrive_2 = t + rand_uniform(arr_t2->min, arr_t2->max);
        }
        else if (next_action == WORK_END) 
        {
            // Закончена обработка процесса
            if (device_status == WORK_T1)
                out_t1 += 1;
            else if (device_status == WORK_T2)
                out_t2 += 1;

            processed_count += 1;
            device_status = FREE;
        }

        if (rc != OK)
        {
            break;
        }

        // if (device_status == FREE && is_empty_q(q1) && is_empty_q(q2))

        if (device_status == FREE) 
        {
            if (!is_empty_q(q1)) 
            {
                q_type in_time;
                pop(q1_time, &in_time);

                avg_time_q1 += t - in_time;

                device_status = WORK_T1;
                
                in_t1 += 1;
                
                q_type work_time;
                rc = pop(q1, &work_time);
                if (rc != OK)
                {
                    break;
                }

                end_time = t + work_time;
            } 
            else if (!is_empty_q(q2)) 
            {
                q_type in_time;
                pop(q2_time, &in_time);

                avg_time_q2 += t - in_time;
                
                device_status = WORK_T2;
                
                in_t2 += 1;
                
                q_type work_time;
                rc = pop(q2, &work_time);
                if (rc != OK)
                {
                    break;
                }

                end_time = t + work_time;
            }
            else
            {
                end_time = INFINITY;
                // free_time += min(next_arrive_1, next_arrive_2) - t;
                // free_time += next_time_point - t;
            }

        }

    }

    if (rc == OK)
    {
        // делим на время
        avg_len_q1 /= t;
        avg_len_q2 /= t;

        // printf("Общее время работы: %.2f\n", t);
        // printf("Время простоя: %.2f\n\n", free_time);

        double avg_t1 = (arr_t1->max + arr_t1->min) / 2;
        double theor_out = out_t1 * avg_t1;
        double percent_error = 100.0 * fabs(t - theor_out) / theor_out;

        printf(
            SEPARATOR_LINE
            "КОЛИЧЕСТВО ЗАЯВОК: %d\n"
            SEPARATOR_LINE
            "СРЕДНЯЯ ДЛИНА ОЧЕРЕДИ\n" 
            SEPARATOR_LINE
            "I-й тип: %.0lf\n"
            "II-й тип: %.0lf\n"
            SEPARATOR_LINE
            "ДЛИНА ОЧЕРЕДЕЙ\n"
            SEPARATOR_LINE
            "I-й тип: %d\n"
            "II-й тип: %d\n"
            SEPARATOR_LINE
            "\n",
            out_t1, 
            ceil(avg_len_q1), ceil(avg_len_q2), 
            len_q(q1), len_q(q2)
        );

        printf(
            "\n\n---- ИТОГОВЫЕ РЕЗУЛЬТАТЫ ----\n"
            SEPARATOR_LINE
            "ВРЕМЯ РАБОТЫ ОА\n" 
            SEPARATOR_LINE
            "Время работы: %.2lf\n"
            "Теор. время работы: %.2lf\n"
            "Расхождение: %.2lf%%\n"
            SEPARATOR_LINE
            "Время простоя: %.2lf\n"
            SEPARATOR_LINE, 
            t, theor_out, percent_error, free_time
        );
        
        printf(
            "\n"
            SEPARATOR_LINE
            "СТАТИСТИКА ВХОДА/ВЫХОДА\n"
            SEPARATOR_LINE
            "Всего вышло: %d\n"
            SEPARATOR_LINE
            "Заявки I-го типа\n" 
            "Вошло: %d\n"
            "Вышло: %d\n"
            SEPARATOR_LINE
            "Заявки II-го типа\n" 
            "Вошло: %d\n"
            "Вышло: %d\n"
            "Выброшено: %d\n"
            SEPARATOR_LINE,
            processed_count,
            in_t1, out_t1,
            in_t2, out_t2, drop_t2
        );

        
        printf(
            "\n"
            SEPARATOR_LINE
            "СРЕДНЕЕ ВРЕМЯ В ОЧЕРЕДИ\n" 
            SEPARATOR_LINE
            "I-й тип: %.3lf\n"
            "II-й тип: %.3lf\n"
            SEPARATOR_LINE,
            avg_time_q1 / out_t1, out_t2 ? avg_time_q2 / out_t2 : 0
        );

    }

    destroy_queue(q1);
    destroy_queue(q2);
    destroy_queue(q1_time);
    destroy_queue(q2_time);

    // printf("rc = %d", rc);

    return rc;
}
