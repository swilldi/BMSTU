#define _GNU_SOURCE
#include "action.h"
#include "exit_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

action_t str_to_action(char *str)
{
    if (strcmp(str, "out") == 0)
        return OUT;
    else if (strcmp(str, "mul") == 0)
        return MUL;
    else if (strcmp(str, "sqr") == 0)
        return SQR;
    else if (strcmp(str, "div") == 0)
        return DIV;

    return ACTION_ERR;
}

error input_action(action_t *action, char *msg)
{
    (void)msg;
    char *line = NULL;
    size_t len = 0;

    // #ifndef FUNC_OUT
    // printf("%s", msg);
    // #endif

    ssize_t s = getline(&line, &len, stdin);
    if (s == -1)
    {
        return INPUT_ERROR;
    }
    else if (line[0] == '\0' || line[0] == '\n')
    {
        free(line);
        return EMPTY_STR;
    }

    line[s - 1] = '\0';
    s -= 1;

    *action = str_to_action(line);
    free(line);

    if (*action == ACTION_ERR)
    {
        return INVALID_INPUT;
    }
    else
    {
        return OK;
    }
}
