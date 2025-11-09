#include <stdio.h>
#include "stack_type.h"
#include "stack_func.h"
#include <string.h>
#include "str_func.h"
#include <stdlib.h>

error pop(my_stack_t *stack, str_t value)
{
    if (stack->sp < stack->down_p)
        return STACK_IS_EMPTY;
    
    strcpy(value, *stack->sp);
    stack->sp -= 1;
    
    return OK;
    
}

error push(my_stack_t *stack, str_t value)
{
    stack->sp += 1;

    if (stack->sp >= stack->down_p + STACK_MAX_LEN)
    {
        stack->sp -= 1;
        return STACK_OVERFLOW;
    }
    
    strcpy(*stack->sp, value);
    return OK;
}


error print_all_stack(my_stack_t *stack)
{
    if (stack->sp < stack->down_p)
        return STACK_IS_EMPTY;

    //  временное хранение элементов
    char data_tmp[STACK_MAX_LEN][STR_MAX_LEN];
    size_t size = 0;

    // печать элементов
    while (pop(stack, data_tmp[size]) != STACK_IS_EMPTY)
    {
        printf("%s\n", data_tmp[size]);
        size++;
    }

    // возвращение элементов в стек
    for (size_t i = size; i-- > 0;)
        push(stack, data_tmp[i]);
    
    return OK;
}

error print_rev_str(my_stack_t *stack)
{
    if (stack->sp < stack->down_p)
        return STACK_IS_EMPTY;

    //  временное хранение элементов
    char data_tmp[STACK_MAX_LEN][STR_MAX_LEN];
    char rev_str[STR_MAX_LEN];
    size_t size = 0;

    // печать элементов
    while (pop(stack, data_tmp[size]) != STACK_IS_EMPTY)
    {
        reverse_str(rev_str, data_tmp[size]);
        printf("%s\n", rev_str);
        size++;
    }

    // возвращение элементов в стек
    for (size_t i = size; i-- > 0;)
        push(stack, data_tmp[i]);
    
    return OK;
}

bool is_full(my_stack_t *stack)
{
    return stack->sp + 1 >= stack->down_p + STACK_MAX_LEN;
}
