#ifndef QUEUE_LIST_FUNC_H__
#define QUEUE_LIST_FUNC_H__

#include <stdbool.h>

#include "exit_code.h"
#include "queue.h"
#include "queue_info.h"

typedef struct queue_list_t queue_list_t;
typedef struct node_t node_t; 

// создание очереди на списке
queue_list_t *create_queue_list(void);
// добавление элемента в очередь
error push_list(queue_list_t *queue, q_type value);
// удаление элемента из очереди
error pop_list(queue_list_t *queue, q_type *value);
// просмотр первого элемента из очереди
error front_list(queue_list_t *queue, q_type *value);
// очередь пустая
bool is_empty_q_list(queue_list_t *queue);
// вывод только заполненных элементов очереди
void print_queue_list(queue_list_t *queue);
// вывод всей очереди даже пустные значения
void print_queue_list_info(queue_list_t *queue);
// Длина очереди
int len_list(queue_list_t *queue);
// Осовобождение выделенной памяти
void destroy_queue_list(queue_list_t *queue);
// Размер node_t
size_t get_size_node_t(void);
// Размер queue_list_t
size_t get_size_queue_list_t(void);

node_t *get_piout_queue_list(queue_list_t *queue);


#endif
