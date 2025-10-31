#include "stdio.h"
#include "io_func.h"
#include "string.h"

error input_str(str_t str, FILE *f)
{
    

    char buff[STR_MAX_LEN + 2];
    if (!fgets(buff, sizeof(buff), f))
        return INPUT_ERR;
    
    size_t len = strlen(buff);
    if (len && buff[len - 1] == '\n')
    {
        len -= 1;
        buff[len] = '\0';
    }

    if (!len)
        return STR_IS_EMPTY;
    else if (len >= STR_MAX_LEN)
        return STR_OVERFLOW;

    strcpy(str, buff);
    
    return OK;
}
