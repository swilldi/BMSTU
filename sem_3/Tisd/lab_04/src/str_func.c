#include "str_func.h"
#include <stdlib.h>
#include <string.h>

void reverse_str(char *str, char *str_orign)
{
    size_t l = strlen(str_orign);
    for (size_t i = 0; i < l; i++)
    {
        str[i] = str_orign[l - i - 1];
    }
    str[l] = '\0';
}
