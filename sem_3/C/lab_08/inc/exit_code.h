#ifndef EXIT_CODE_H__
#define EXIT_CODE_H__

typedef enum
{
    OK,
    MEM_ERR = 10,
    ZERO_MATRIX,
    IO_ERR,
    RANGE_ERR,
    EMPTY_STR,
    OVERFLOW_STR,
    FEW_ARGS_ERR,
    MANY_ARGS_ERR,
    INVALID_ACTION,
    NOT_REV_MATRIX,
    FILE_OPEN_ERR,
    FILE_EMPTY_ERR,
    INVALID_SIZE
} error;

#endif
