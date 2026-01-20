#ifndef ACTION_T_H__
#define ACTION_T_H__

#include "exit_code.h"

typedef enum
{
    OUT,
    MUL,
    SQR,
    DIV,
    ACTION_ERR
} action_t;

action_t str_to_action(char *str);
error input_action(action_t *action, char *msg);

#endif
