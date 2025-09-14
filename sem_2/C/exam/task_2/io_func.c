#include <stdio.h>
#include "info.h"
#include "exit_code.h"
#include "io_func.h"
#include <string.h>


int input_str(char *str)
{
    if (fgets(str, STR_LEN + 1, stdin) == NULL)
    {
        return ERR_UNKNOWN;
    }

    size_t len = strlen(str);
    if (len == 0)
    {
        return ERR_EMPTY;
    }
    if (len >= STR_LEN)
    {
        return ERR_OVERFLOW;
    }
    
    str[len - 1] = '\0';
    return OK;
}
