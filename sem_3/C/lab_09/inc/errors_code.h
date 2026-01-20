#ifndef ERRORS_CODE_H
#define ERRORS_CODE_H

typedef enum
{
    OK = 0,
    ARGS_TOO_FEW = 10,
    INVALID_ARGS,
    FILE_IS_EMPTY,
    INVALID_FILE_CONTENT,
    FILE_OPEN_ERROR = 20,
    READ_ERROR,
    NOT_NUM = 30,
    NOT_NATURAL_NUM,
    EMPTY_STR,
    MEMORY_ERR = 40
} exit_code_t;

#define OK 0

#endif
