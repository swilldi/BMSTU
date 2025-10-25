#include "stack_type.h"

typedef enum 
{
    STACK_OVERFLOW,
    STACK_IS_EMPTY
} error;


error pop(stack_t *stack, STACK_VALUE_TYPE value)
{
    if (stack->sp - 1 < stack->down_p)
        return STACK_IS_EMPTY;
    
}

error push(stack_t *stack, STACK_VALUE_TYPE value)
{
    if (stack->sp + 1 >= stack->up_p)
            return STACK_OVERFLOW;
    
    stack->sp++;
    *(stack->sp) = value;   
}


int main(void)
{
    stack_t stack;
    
    
}
