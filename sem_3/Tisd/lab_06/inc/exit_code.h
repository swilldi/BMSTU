#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum
{
    OK,

    INVALID_INPUT,
    CMD_OUT_OF_RANGE,
    READ_ERROR,
    STR_OVERFLOW,
    STR_EMPTY,
    MEMORY_ERROR,
    VALUE_ALREADY_IN_TREE,
    VALUE_NOT_IN_TREE,
    OPEN_FILE_ERROR,
    EMPTY_FILE,
} error;

#endif
