#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum 
{
    OK,
    INVALID_INPUT,
    INVALID_CMD,

    STR_OVERFLOW,
    STR_EMPTY,
    MEMORY_ERROR,
    OPEN_FILE_ERR,
    EMPTY_FILE,

    VALUE_EXITS,
    VALUE_NOT_EXITS,
    
    
} error;

#endif
