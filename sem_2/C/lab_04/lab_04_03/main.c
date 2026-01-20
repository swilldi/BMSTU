#include "errors.h"
#include "string_func.h"
#include "string_info.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    // ввод строки
    char str[STRING_SIZE];
    if (fgets(str, STRING_SIZE, stdin) == NULL)
    {
        printf(EMPTY_RES_STRING_MESSAGE);
        return EMPTY_RES_STRING_ERROR;
    }

    if (strlen(str) == STRING_SIZE - 1 && (str[STRING_SIZE - 2] != '\n' || str[STRING_SIZE - 2] != '\0'))
    {
        printf(STRING_OWERFLOW_MESSAGE);
        return STRING_OWERFLOW_ERROR;
    }

    // формируем массив слов
    char words[STRING_SIZE / WORD_SIZE][WORD_SIZE];
    size_t count;
    if (str_to_words(str, words, &count) != 0)
    {
        printf(WORD_OWERFLOW_MESSAGE);
        return WORD_OWERFLOW_ERROR;
    }

    // printf("%lu\n", count);
    // for (size_t i = 0; i < count; i++)
    // {
        // printf("%s ", words[0]);
    // }
    // printf("\n");
    
    if (count < 2)
    {
        printf(EMPTY_RES_STRING_MESSAGE);
        return EMPTY_RES_STRING_ERROR;
    }

    // формирование новой строки
    char new_str[STRING_SIZE];
    new_str_generate(words, count, new_str);

    // printf()
    if (new_str[0] != '\0')
    {
        printf("Result: %s\n", new_str);
    }
    else
    {
        printf(EMPTY_RES_STRING_MESSAGE);
        return EMPTY_RES_STRING_ERROR;
    }
}
