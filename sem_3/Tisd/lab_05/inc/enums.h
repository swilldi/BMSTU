#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum 
{
    EXIT,
    PUSH,
    POP,
    PRINT_VALUE,

    MAX_CMD_ACTION,
    NO_CMD,
    CONTINUE
} CMD_ACTION;

typedef enum 
{
    EMULATE_LIST_QUEUE = 1,
    PROCESS_DEVICE = 2,
    COMPARE = 3,

    MAX_PROGRAMM_MODE
} programm_mode_t;

#endif
