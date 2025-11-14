#ifndef QUEUE_ARRAY_FUNC_H__
#define QUEUE_ARRAY_FUNC_H__

#include <stdbool.h>
#include "exit_code.h"
#include "queue_info.h"

typedef struct queue_array_t queue_array_t;

queue_array_t *create_queue_array(void);
// добавление элемента в очередь
error push_array(queue_array_t *queue, q_type value);
// удаление элемента из очереди
error pop_array(queue_array_t *queue, q_type *value);
// просмотр первого элемента из очереди
error front_array(queue_array_t *queue, q_type *value);
// вывод только заполненных элементов очереди
void print_queue_array(queue_array_t *queue);
// вывод всей очереди даже пустные значения
void print_queue_array_full(queue_array_t *queue);
// очередь пустая
bool is_empty_q_arr(queue_array_t *queue);
// Длина очереди
int len_array(queue_array_t *queue);
// Осовобождение выделенной памяти
void destroy_queue_array(queue_array_t *queue);

#endif
