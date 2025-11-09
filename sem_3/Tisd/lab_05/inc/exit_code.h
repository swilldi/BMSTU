#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum
{
    OK,
    QUEUE_OVERFLOW,
    QUEUE_IS_EMPTY,
    INVALID_INPUT,
    INVALID_CMD_RANGE,
    MEM_ERR
} error;

#endif 
