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


int input_pos_int(int *num, int max_num)
{
    int rc = OK;
    if (scanf("%d", num) != 1 || *num >= max_num)
        rc = INVALID_INPUT;
    
    while (fgetc(stdin) != '\n');

    return rc;
}

int input_char(char *c)
{
    int rc = OK;
    if (scanf("%c", c) != 1)
        rc =  INVALID_INPUT;
    
    while (fgetc(stdin) != '\n');

    return rc;
}

void print_err_msg(int rc)
{
    switch (rc)
    {
        case INVALID_INPUT:
            printf("Некоректный ввод");
            break;
        case STR_OVERFLOW:
            printf("Строка длинее %d символов", STR_LEN);
            break;
        case STR_EMPTY:
            printf("Пустая строка");
            break;
        case VALUE_EXITS:
            printf("Значение уже существует");
            break;
        case VALUE_NOT_EXITS:
            printf("Значения не существует");
            break;
        case MEMORY_ERROR:
            printf("Ошибка выделения памяти");
            break;
        case INVALID_CMD:
            printf("Некоректная команда");
            break;
        // case :
        //     printf("");
        //     break;
    }
    printf("\n");
}
