#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum 
{
    OK = 0,
    STACK_OVERFLOW = 10,
    STACK_IS_EMPTY,
    INPUT_ERR,
    STR_IS_EMPTY,
    STR_OVERFLOW,
    CMD_RANGE_ERR,
    HISTORY_IS_EMPTY,
    MEMORY_ERR
} error;

#endif
