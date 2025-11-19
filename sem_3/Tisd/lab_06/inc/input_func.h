#ifndef INPUT_FUNC_H__
#define INPUT_FUNC_H__

#include <stdio.h>
#include "tree.h"
#include "exit_code.h"


int input_cmd(int *cmd, int max_value)
{

    #ifndef FUNC_OUT
    printf("Введите команду: ");
    #endif

    if (scanf("%d", cmd) != 1)
        return INVALID_INPUT;
    if (*cmd < 0 || *cmd >= max_value)
        return CMD_OUT_OF_RANGE;

    // очищение буффера stdin
    int ch = fgetc(stdin);
    while (ch != '\n' && !feof(stdin))
        ch = fgetc(stdin);
    
    return OK;
}

int input_str(char *str, char *msg)
{

    #ifndef FUNC_OUT
    if (msg == NULL)
        printf("Введите строку: ");
    else
        printf("%s", msg);
    #endif

    char tmp_str[STR_LEN + 10];
    if (fgets(tmp_str, STR_LEN + 10, stdin) == NULL)
        return READ_ERROR;
    
    size_t len = strlen(tmp_str);
    if (len && tmp_str[len - 1] == '\n')
    {
        tmp_str[len - 1] = '\0';
        len -= 1;
    }

    if (!len)
        return STR_EMPTY;
    if (len > STR_LEN)
        return STR_OVERFLOW;

    strcpy(str, tmp_str);
        
    return OK;

}

int input_char(char *symbol)
{

    #ifndef FUNC_OUT
    printf("Введите символ: ");
    #endif

    if (scanf("%c", symbol) != 1)
        return INVALID_INPUT;

    int ch = fgetc(stdin);
    while (ch != '\n' && !feof(stdin))
        ch = fgetc(stdin);
    
    return OK;
}

#endif
