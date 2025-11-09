#ifndef QUEUE_LIST_FUNC_H__
#define QUEUE_LIST_FUNC_H__

#include <stdbool.h>

#include "exit_code.h"
#include "queue_info.h"

typedef struct queue_list_t queue_list_t;
typedef struct node_t node_t; 

// создание очереди на списке
queue_list_t *create_queue_list(void);
// добавление элемента в очередь
error push_list(queue_list_t *queue, q_type value);
// удаление элемента из очереди
error pop_list(queue_list_t *queue, q_type *value);
// вывод только заполненных элементов очереди
void print_queue_list(queue_list_t *queue);
// вывод всей очереди даже пустные значения
void print_queue_list_info(queue_list_t *queue);

#endif
