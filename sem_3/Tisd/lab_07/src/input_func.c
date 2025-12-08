#include <stdio.h>
#include <string.h>

#include "exit_code.h"

#define TEMP_STR_LEN 256
int input_str(char *str, int max_len)
{
    char temp_str[TEMP_STR_LEN];
    if (fgets(temp_str, TEMP_STR_LEN, stdin) == NULL)
        return INVALID_INPUT;
    
    int len = strlen(temp_str);
    if (len && temp_str[len - 1] == '\n')
    {
        temp_str[len - 1] = '\0';
        len -= 1;
    }

    if (!len)
        return STR_EMPTY;
    if (len >= max_len)
        return STR_OVERFLOW;

    strcpy(str, temp_str);
    
    return OK;
    
}
