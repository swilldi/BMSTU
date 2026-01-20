#ifndef ACTION_T_H__
#define ACTION_T_H__

typedef enum
{
    INSERT,
    POPBACK,
    REVERSE,
    SORT,
    ACTION_ERR
} action_t;

action_t str_to_action(char *str);

#endif
