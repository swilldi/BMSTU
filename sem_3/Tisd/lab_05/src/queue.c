#include "queue.h"


error push(queue_t *queue, q_type value)
{
    if (queue->mode == ARRAY)
        return push_array(queue->data.arr, value);
    else if (queue->mode == LIST)
        return push_list(queue->data.list, value);
    else
        // TODO Придумать ощибку
        return CMD_ERROR;
}

error pop(queue_t *queue, q_type *value)
{
    if (queue->mode == ARRAY)
        return pop_array(queue->data.arr, value);
    else if (queue->mode == LIST)
        return pop_list(queue->data.list, value);
    else
        // TODO Придумать ощибку
        return CMD_ERROR;
}

error is_empty_q(queue_t *queue)
{
    if (queue->mode == ARRAY)
        return is_empty_q_arr(queue->data.arr);
    else if (queue->mode == LIST)
        return is_empty_q_list(queue->data.list);
    else
        // TODO Придумать ощибку
        return CMD_ERROR;
}

int len_q(queue_t *queue)
{
    if (queue->mode == ARRAY)
        return len_array(queue->data.arr);
    else if (queue->mode == LIST)
        return len_list(queue->data.list);
    
    return -1;
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
        {
            free(queue);
            return NULL;
        }
    }
    else if (mode == LIST)
    {
        queue->data.list = create_queue_list();
        if (!queue->data.list)
        {
            free(queue);
            return NULL;
        }
    }
    else
    {
        free(queue);
        return NULL;
    }

    return queue;
}

void destroy_queue(queue_t *queue)
{
    if (queue->mode == ARRAY)
        destroy_queue_array(queue->data.arr);
    else if (queue->mode == LIST)
        destroy_queue_list(queue->data.list);
    
    free(queue);
}
