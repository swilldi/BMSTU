#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum 
{
    OK,
    INVALID_INPUT,
    STR_OVERFLOW,
    STR_EMPTY,
    VALUE_EXITS,
    VALUE_NOT_EXITS,
    MEMORY_ERROR,
    INVALID_CMD,
    
    OPEN_FILE_ERR,
} error;

#endif
