#define STACK_VALUE_TYPE char*

typedef struct
{
    STACK_VALUE_TYPE up_p;  //
    STACK_VALUE_TYPE down_p;   
    
    STACK_VALUE_TYPE sp;
} stack_t;
