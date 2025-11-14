#ifndef QUEUE_H__
#define QUEUE_H__

#include <stdlib.h>
#include "queue_array_func.h"
#include "queue_list_func.h"
#include "queue_info.h"

typedef enum
{
    ARRAY,
    LIST,

    MAX_QUEUE_MODE
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

// добавлние элемента
error push(queue_t *queue, q_type value);

// удаление элемента
error pop(queue_t *queue, q_type *value);

// проверка на пустоту
error is_empty_q(queue_t *queue);

// получение длины
int len_q(queue_t *queue);

// создание очереди
queue_t *create_queue(queue_mode_t mode);

// освобождение выделенной очереди
void destroy_queue(queue_t *queue);

#endif
