#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum
{
    OK,
    INVALID_ARGS_COUNT,
    INVALID_ACTION,
    FILE_OPEN_ERR,
    EMPTY_FILE,
    INVALID_DATA,
    MEMORY_ERR,
    EMPTY_LIST,
    INVALID_INPUT,
    INVALID_INDEX,
    EMPTY_STR,
    INPUT_ERROR,
    RES_IS_ZERO,
    DIV_BY_ZERO
} error;

#endif
