#ifndef ENUMS_H__
#define ENUMS_H__

typedef enum
{
    TREE_EMULATE = 1,
    RUN_TESTS = 2,

    MAX_PROG_MODE
} prog_mode_t;

typedef enum
{
    EXIT = 0,
    
    ADD,
    DEL,

    COUNT_BY_LETTER,
    CMP_TREE_AND_FILE,
    
    READ_TREE,

    CLEAR_QUICK_EXPORT,
    QUICK_EXPORT,
    CLEAR_EXPORT,
    EXPORT,

    MAX_ACTION_CMD,
    CONTINUE
} action_cmd_t;

#endif
