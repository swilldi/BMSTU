#ifndef QUEUE_ARRAY_FUNC_H__
#define QUEUE_ARRAY_FUNC_H__

#include <stdbool.h>
#include "exit_code.h"
#include "queue_info.h"

typedef struct queue_array_t queue_array_t;

// добавление элемента в очередь
error push_array(queue_array_t *queue, q_type value);
// удаление элемента из очереди
error pop_array(queue_array_t *queue, q_type *value);
// вывод только заполненных элементов очереди
void print_queue_array(queue_array_t *queue);
// вывод всей очереди даже пустные значения
void print_queue_array_full(queue_array_t *queue);

#endif
