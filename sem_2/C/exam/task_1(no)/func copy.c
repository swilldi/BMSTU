// прочитать строку
int input_str(char *str)
{
    if (fgets(str, STR_LEN + 1, stdin) == NULL)
    {
        return 1;
    }
    if (strlen(str) > STR_LEN)
    {
        return 2;
    }
    
    return 0;
}

// из строки числа в массив
int action(char *str, int *res)
{
    char *part;
    part = strtok(str, SEPARATORS);
    int cur = 0;
    while (part != NULL)
    {
        if (str_to_num(part, &cur) == 0)
        {
            *res += cur;
        }
        // printf("%s\n", part);
        part = strtok(NULL, SEPARATORS);
    }

    if (*res == 0)
    {
        return 1;
    }

    return 0;
}

int str_to_num(char *str, int *num)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 1;
        }
        else
        {
            *num = *num * 10 + (int)('0' - str[i]);
        }
    }
    return 0;
}
