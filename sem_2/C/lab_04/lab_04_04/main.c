#include "errors.h"
#include "string_func.h"
#include "string_info.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[STRING_SIZE];
    if (fgets(str, STRING_SIZE, stdin) == NULL)
    {
        return 1;
    }

    if (strlen(str) == STRING_SIZE - 1 && str[STRING_SIZE - 2] != '\n')
    {
        return 2;
    }

    size_t len = strlen(str);
    if (len)
    {
        printf(contains_valid_ip(str) ? "YES\n" : "NO\n");
    }
    return 0;
}
