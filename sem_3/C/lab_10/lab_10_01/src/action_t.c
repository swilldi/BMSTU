#include "action_t.h"
#include <string.h>

action_t str_to_action(char *str)
{
    if (strcmp(str, "insert") == 0)
        return INSERT;
    else if (strcmp(str, "popback") == 0)
        return POPBACK;
    else if (strcmp(str, "reverse") == 0)
        return REVERSE;
    else if (strcmp(str, "sort") == 0)
        return SORT;

    return ACTION_ERR;
}
