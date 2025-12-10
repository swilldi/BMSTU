#include <stdio.h>
#include <string.h>

#include "common_define.h"
#include "exit_code.h"



int read_str(char *str, int max_len, FILE *f)
{
    char temp_str[TEMP_STR_LEN];
    if (fgets(temp_str, TEMP_STR_LEN, f) == NULL)
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

int input_str(char *str, int max_len)
{
    return read_str(str, max_len, stdin);
}
