#include <stdio.h>
#include "queue.h"

// ----------------------------------
// ОБЪЯВЛЕНИЯ ВНУТРЕНИХ ФУНКЦИЙ     |
// ----------------------------------

static node_t *create_node(q_type value);
// особождение памяти из под элемента списка
static void destroy_node(node_t *node);
// инициализация нового элемента
static void init_node(node_t *node, q_type value);
// инициализация очереди на списке
static void init_queue_list(queue_list_t *queue);
// очередь полная
static bool is_full_q_list(queue_list_t *queue);


// ----------------------------------
// ОПИСАНИЕ СТРУКТУРЫ               |
// ----------------------------------

struct queue_list_t
{
    node_t *pin;
    node_t *pout;
};

struct node_t
{
    q_type value;
    node_t *pnext;
};


// ----------------------------------
// ВНУТРЕНИЕ ФУНКЦИИ                |
// ----------------------------------

// инициализация очереди на списке
static void init_queue_list(queue_list_t *queue)
{
    queue->pin = NULL;
    queue->pout = NULL;
}

// создание одного элемента списка
static node_t *create_node(q_type value)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node)
        init_node(new_node, value);

    return new_node;
}

// особождение памяти из под элемента списка
static void destroy_node(node_t *node)
{
    free(node);
}

// инициализация нового элемента
static void init_node(node_t *node, q_type value)
{
    node->value = value;
    node->pnext = NULL;
}

// очередь полная
static bool is_full_q_list(queue_list_t *queue)
{
    size_t count = 0;
    node_t *node = queue->pout;
    while (node)
    {
        count += 1;
        node = node->pnext;
    }

    return count == QUEUE_LEN ? true : false;
}


// ----------------------------------
// ВНЕШНИИ ФУНКЦИИ                  |
// ----------------------------------

// создание очереди на списке
queue_list_t *create_queue_list(void)
{
    queue_list_t *queue = malloc(sizeof(queue_list_t));
    if (queue)
        init_queue_list(queue);
    
    return queue;
}

void destroy_queue_list(queue_list_t *queue)
{
    node_t *pnode = queue->pout;
    while (pnode)
    {
        node_t *pnext = pnode->pnext;
        destroy_node(pnode);
        pnode = pnext;
    }
    free(queue);
}

// добавление элемента в очередь
error push_list(queue_list_t *queue, q_type value)
{
    // if (is_full_q_list(queue))
    //     return QUEUE_OVERFLOW;

    // создание нового элемента 
    node_t *new_node = create_node(value);
    if (!new_node)
        return MEM_ERR;

    // TODO: ПУСТАЯ ОЧЕРЕДЬ
    if (queue->pout == NULL)
        queue->pout = new_node;
    else
        queue->pin->pnext = new_node;
    
    queue->pin = new_node;

    return OK;
}
// удаление элемента из очереди
error pop_list(queue_list_t *queue, q_type *value)
{
    if (is_empty_q_list(queue))
        return QUEUE_IS_EMPTY;

    node_t *pop_node = queue->pout;

    *value = pop_node->value;
    queue->pout = pop_node->pnext;

    destroy_node(pop_node);

    return OK;
}

// просмотр первого элемента из очереди
error front_list(queue_list_t *queue, q_type *value)
{
    if (is_empty_q_list(queue))
        return QUEUE_IS_EMPTY;

    *value = queue->pout->value;

    return OK;
}

// очередь пустая
bool is_empty_q_list(queue_list_t *queue)
{
    return queue->pout == NULL ? true : false;
}

int len_list(queue_list_t *queue)
{
    int count = 0;
    node_t *pnode = queue->pout;

    while (pnode)
    {
        count++; 
        pnode = pnode->pnext;
    }

    return count;
}

// вывод только заполненных элементов очереди
void print_queue_list(queue_list_t *queue)
{   
    node_t *node = queue->pout;
    while (node)
    {
        printf("%10f\n", node->value);
        node = node->pnext;
    }
}

// вывод только заполненных элементов очереди
void print_queue_list_info(queue_list_t *queue)
{   
    bool is_first = true;
    node_t *node = queue->pout;
    while (node)
    {
        #ifdef FUNC_OUT
        printf("%-10.3f", node->value);
        #else
        printf("%10.3f", node->value);
        #endif
        
        #ifndef FUNC_OUT
        printf(" (%p)", (void*)node);
        #endif
        node = node->pnext;

        if (is_first)
        {
            is_first = false;
            #ifndef FUNC_OUT
            printf(" <-- out");
            #endif
        }

        printf("\n");
    }
    
    #ifndef FUNC_OUT
    if (!is_full_q_list(queue))
    {
        
        printf("%10s (0x000000000)", "empty");
        if (is_first)
            printf("<-- out");

        printf(" <-- in\n");
    }
    #endif
    
}

node_t *get_piout_queue_list(queue_list_t *queue)
{
    return queue->pout;
}

// Размер node_t
size_t get_size_node_t(void)
{
    return sizeof(node_t);
}
// Размер queue_list_t
size_t get_size_queue_list_t(void)
{
    return sizeof(queue_list_t);
}
