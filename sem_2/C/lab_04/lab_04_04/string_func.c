#include "string_func.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int is_valid_num(char *start, char *end)
{
    int len = end - start + 1;
    if (len < 1 || len > 3)
    {
        return 0;
    }
    // if (len > 1 && *start == '0')

    int num = 0;
    for (const char *p = start; p <= end; p++)
    {
        if (!isdigit(*p))
        {
            return 0;
        }
        num = num * 10 + (*p - '0');
    }

    return (num >= 0 && num < 256);
}

int contains_valid_ip(char *str)
{
    char *p = str;
    int dots = 0;
    char *num_start = NULL;
    char *last_dot_pos = NULL;
    short int valid_num = 0;

    while (*p == ' ') 
    {
        p++;
    }

    while (*p)
    {
        if (valid_num)
        {
            // printf("p = %d %d\n", *p, *p != ' ' || *p != '\0' || *p != '\n');
            // printf("p = %d %d\n", *p, *p > 32);
            // if (*p != ' ' && *p != '\0' && *p != '\n')
            if (*p > 32)
            {
                return 0;
            }
        }
        if (isdigit(*p))
        {
            if (!num_start)
            {
                num_start = p;
            }
        }
        else if (*p == '.')
        {
            if (!num_start)
            {
                return 0;
            }
            if (last_dot_pos && (p - last_dot_pos == 1))
            {
                return 0;
            }
            if (!is_valid_num(num_start, p - 1))
            {
                return 0;
            }

            dots++;
            last_dot_pos = p;
            num_start = NULL;
        }
        else
        {
            dots = 0;
            num_start = NULL;
            last_dot_pos = NULL;
        }

        if (dots == 3)
        {
            char *end = p + 1;
            // printf("%c == ",  *end);
            while (*end && isdigit(*end))
                end++;
            // printf("%d\n", *end);
            valid_num = is_valid_num(last_dot_pos + 1, end - 1);
            // printf("%d\n", valid_num);
            // printf("%d\n", *end);
            p = end;
            // if (is_valid_num(last_dot_pos + 1, end - 1))
            dots = 0;
            continue;
        }
        p++;
    }
    return valid_num;
}
