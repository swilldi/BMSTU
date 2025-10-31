#include "stack_list_func.h"
#include "stdio.h"
#include "exit_code.h"
#include "stdlib.h"
#include "string.h"
#include "str_func.h"


#define START_COUNT 2
#define EXTRACT_K 2

stack_list_t* create_stack_node(stack_list_t *stack, str_t str)
{
    stack_list_t *node = malloc(sizeof(stack_list_t));
    if (node)
    {
        node->prev = stack;
        strcpy(node->sp, str);
        node->ind = stack->ind + 1;
    }
    
    return node;
}

void free_stack_list(stack_list_t *stack)
{
    if (stack == NULL)
        return;

    stack_list_t *node;
    while (stack->prev)
    {
        node = stack;
        stack = stack->prev;

        free(node);
    }
    free(stack);
}

error pop_l(stack_list_t **stack, str_t value)
{
    if (!(*stack))
        return STACK_IS_EMPTY;
    
    stack_list_t *new_top = (*stack)->prev;

    strcpy(value, (*stack)->sp);
    free(*stack);
    *stack = new_top;

    return OK;
}

error push_l(stack_list_t **stack, str_t value)
{
    stack_list_t *new_node = malloc(sizeof(stack_list_t));
    if (!new_node)
        return MEMORY_ERR;

    strcpy(new_node->sp, value);
    new_node->prev = *stack;

    *stack = new_node;
    return OK;
}

error print_all_stack_list(stack_list_t *stack)
{
    if (!stack)
        return STACK_IS_EMPTY;
    
    #ifndef FUNC_OUT
    printf("Содержимое стека\n");
    #endif
    //  временное хранение элементов
    stack_list_t *stack_tmp = stack;
    while (stack_tmp)
    {
        printf("%s\n", stack_tmp->sp);
        stack_tmp = stack_tmp->prev;
    }

    return OK;
}

error print_all_stack_list_address(stack_list_t *stack)
{
 
    if (!stack)
    {
        return STACK_IS_EMPTY;
    }

    printf("Содержимое стека с адресами\n");

    // печать элементов
    stack_list_t *stack_tmp = stack;
    while (stack_tmp)
    {
        printf("%s (%p)\n", stack_tmp->sp, (void*)stack_tmp);
        stack_tmp = stack_tmp->prev;
    }

    return OK;
}


del_history_arr *create_del_history_arr(void)
{
    del_history_arr *arr = malloc(sizeof(del_history_arr)); 
    if (!arr)
        return NULL;
    
    arr->data = malloc(sizeof(stack_list_t*) * START_COUNT);
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    
    arr->max_len = START_COUNT;
    arr->len = 0;
    return arr;
}

void free_history_arr(del_history_arr *arr)
{
    if (!arr)
        return;

    free(arr->data);
    free(arr);
}

error extern_arr(del_history_arr *arr)
{
    printf(" ___РАСШИРЕНИЕ___\n");
    stack_list_t **tmp = realloc(arr->data, arr->max_len * 2);
    if (!tmp)
        return MEMORY_ERR;
        
    
    arr->data = tmp;
    arr->max_len *= 2;

    return OK;
}

error add_elem_to_history_arr(del_history_arr *arr, stack_list_t *value)
{
    error rc;
    if (arr->len == arr->max_len)
    {
        rc = extern_arr(arr);
        if (!rc)
            return rc;
    }

    arr->data[arr->len] = value;
    arr->len++;

    return OK;
}

error print_history_arr(del_history_arr *arr)
{
    if (arr->len == 0)
    {
        return HISTORY_IS_EMPTY;
    }

    printf("История удаления (адресса):\n");
    for (size_t i = 0; i < arr->len; i++)
    {
        printf("%lu: %p\n", i + 1, (void*)arr->data[i]);
    }

    return OK;
}


error print_rev_str_l(stack_list_t **stack)
{
    
    if (!stack)
    {
        return STACK_IS_EMPTY;
    }
    
    #ifndef FUNC_OUT
    printf("Содержимое стека\n");
    #endif
    //  временное хранение элементов
    char data_tmp[STACK_MAX_LEN][STR_MAX_LEN];
    char rev_str[STR_MAX_LEN];
    size_t size = 0;

    // печать элементов
    while (pop_l(stack, data_tmp[size]) != STACK_IS_EMPTY)
    {
        #ifndef FUNC_OUT
        printf("Значение: ");
        #endif
        reverse_str(rev_str, data_tmp[size]);
        printf("%s\n", rev_str);
        size++;
    }

    // возвращение элементов в стек
    for (size_t i = size; i-- > 0;)
        push_l(stack, data_tmp[i]);

    return OK;
}
