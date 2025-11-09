#ifndef STACK_FUNC_H__
#define STACK_FUNC_H__

#include "stack_type.h"
#include "exit_code.h"
#include <stdbool.h>

error pop(my_stack_t *stack, str_t value);
error push(my_stack_t *stack, str_t value);
error print_all_stack(my_stack_t *stack);
error print_rev_str(my_stack_t *stack);
bool is_full(my_stack_t *stack);


#endif
