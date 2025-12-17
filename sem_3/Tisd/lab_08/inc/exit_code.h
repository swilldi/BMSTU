#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum
{
    OK = 0,

    INVALID_PARAM,
    INVALID_RANGE,
    READ_ERROR,
    MEM_ERROR,
    FILE_OPEN_ERROR,
    EDGE_NOT_EXITS,
    EDGE_ALREADY_EXITS,
    INVALID_DATA,
    INVALID_INPUT,
    
} errors;

#endif
