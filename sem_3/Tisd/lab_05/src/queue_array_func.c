#include <stdio.h>
#include "queue_array_func.h"


// ----------------------------------
// ОБЪЯВЛЕНИЯ ВНУТРЕНИХ ФУНКЦИЙ     |
// ----------------------------------

// инициализация очереди
static void init_queue_array(queue_array_t *q);
// очередь полная
static bool is_full_q_arr(queue_array_t*);


// ----------------------------------
// ОПИСАНИЕ СТРУКТУРЫ               |
// ----------------------------------

struct queue_array_t
{
    q_type *pin;
    q_type *pout;

    q_type data[QUEUE_LEN];
    size_t count;
};


// ----------------------------------
// ВНУТРЕНИЕ ФУНКЦИИ                |
// ----------------------------------

// инициализация очереди
static void init_queue_array(queue_array_t *q)
{
    q->pin = q->pout = q->data;
    q->count = 0;
}

// очередь полная
static bool is_full_q_arr(queue_array_t *queue)
{
    return queue->count == QUEUE_LEN;
}


// ----------------------------------
// ВНЕШНИИ ФУНКЦИИ                  |
// ----------------------------------

// создание очереди на статическом массиве
queue_array_t *create_queue_array(void)
{
    queue_array_t *queue = malloc(sizeof(queue_array_t));
    if (queue)
        init_queue_array(queue);
    
    return queue;
}

// добавление элемента в очередь
error push_array(queue_array_t *queue, q_type value)
{
    if (is_full_q_arr(queue))
        return QUEUE_OVERFLOW;
    
    *(queue->pin) = value;
    queue->pin += 1;
    queue->count += 1;

    if (queue->pin == queue->data + QUEUE_LEN)
        queue->pin = queue->data;

    return OK;
}

// удаление элемента из очереди
error pop_array(queue_array_t *queue, q_type *value)
{
    if (is_empty_q_arr(queue))
        return QUEUE_IS_EMPTY;
    
    *value = *queue->pout;
    queue->pout += 1;
    queue->count -= 1;

    if (queue->pout == queue->data + QUEUE_LEN)
        queue->pout = queue->data;

    return OK;
}

// просмотр первого элемента из очереди
error front_array(queue_array_t *queue, q_type *value)
{
    if (is_empty_q_arr(queue))
        return QUEUE_IS_EMPTY;

    *value = *queue->pout;

    return OK;
}

// Длина очереди
int len_array(queue_array_t *queue)
{
    return queue->count;
}

// очередь пустая
bool is_empty_q_arr(queue_array_t *queue)
{
    return queue->count == 0;
}

// вывод с
void print_queue_array(queue_array_t *queue)
{
    q_type *ptmp = queue->pout;
    while (ptmp < queue->pin)
    {
        printf("%f\n", *ptmp);
        ptmp += 1;
    }
}

// вывод всей очереди даже пустные значения
void print_queue_array_full(queue_array_t *queue)
{
    for (size_t i = 0; i < QUEUE_LEN; i++)
    {
        if ((!(queue->data + i < queue->pout && queue->data + i >= queue->pin) && queue->pin < queue->pout) || 
            ((queue->data + i >= queue->pout && queue->data + i < queue->pin && queue->pin > queue->pout)) ||
            (queue->pin == queue->pout && queue->count == QUEUE_LEN))
            printf("%10.4f", queue->data[i]);
        else
            printf("%10s", "empty");
        
        if (queue->data + i == queue->pin)
            printf(" <-- in");
        if (queue->data + i == queue->pout)
            printf(" <-- out");
        
        printf("\n");
    }
}

// Освобождение выделенной памяти
void destroy_queue_array(queue_array_t *queue)
{
    free(queue->data);
    free(queue);
}
