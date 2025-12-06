#ifndef STACK_LIST_FUNC_H__
#define STACK_LIST_FUNC_H__

#include "stack_type.h"
#include "stack_list_func.h"
#include "exit_code.h"
#include <stdlib.h>

typedef struct 
{
    stack_list_t **data;
    size_t len;
    size_t max_len;
} del_history_arr;

error print_all_stack_list(stack_list_t *stack);
stack_list_t* create_stack_node(stack_list_t *stack, str_t str);
error pop_l(stack_list_t **stack, str_t value);
error push_l(stack_list_t **stack, str_t value);
del_history_arr *create_del_history_arr(void);
error add_elem_to_history_arr(del_history_arr *arr, stack_list_t *value);
error print_history_arr(del_history_arr *arr);
error print_all_stack_list_address(stack_list_t *stack);
error print_rev_str_l(stack_list_t **stack);
void free_stack_list(stack_list_t *stack);
void free_history_arr(del_history_arr *arr);

#endif
