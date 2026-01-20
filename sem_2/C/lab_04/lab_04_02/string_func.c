/*
Ввести одну строку. Для каждого слова подсчитать количество его встреч в
исходной строке. Программа должна вывести пары «слово количество-встреч».
Каждая пара выводится на отдельной строке. Слова выводятся в том порядке,
в котором они встретились в исходной строке.
*/

#include "string_func.h"
#include "errors.h"
#include "string_info.h"
#include <stdio.h>
#include <string.h>

int read_line(char str[])
{
    char ch;
    size_t i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < STRING_SIZE - 1)
        {
            str[i] = ch;
            i++;
        }
        else
        {
            return STRING_OWERFLOW_ERROR;
        }
    }
    str[i] = '\0';
    return 0;
}

int to_words(char str[], char words[STRING_SIZE / WORD_SIZE][WORD_SIZE], size_t *count)
{
    short int ind = 0, i = 0;
    char word[WORD_SIZE];
    while (*str != '\0')
    {
        if (strchr(SEPARATORS, *str) == NULL)
        {
            if (i == WORD_SIZE - 1)
            {
                return WORD_OWERFLOW_ERROR;
            }
            word[i] = *str;
            i++;
        }
        else if (i != 0)
        {
            word[i] = '\0';
            strncpy(words[ind], word, WORD_SIZE);
            i = 0;
            ind++;
        }

        str++;
    }

    if (i != 0)
    {
        word[i] = '\0';
        strncpy(words[ind], word, WORD_SIZE);
        i = 0;
        ind++;
    }

    *count = ind;
    return 0;
}

int count_word(char words[STRING_SIZE / WORD_SIZE][WORD_SIZE], char finded_word[STRING_SIZE / WORD_SIZE][WORD_SIZE], int word_count[STRING_SIZE / WORD_SIZE], size_t count)
{
    size_t finded_count = 0;
    char word[WORD_SIZE];
    for (size_t i_word = 0; i_word < count; i_word++)
    {
        strncpy(word, words[i_word], WORD_SIZE);
        short int is_new = 1;
        // printf("%s | ", word);
        for (size_t i = 0; i < finded_count; i++)
        {
            if (strncmp(finded_word[i], word, WORD_SIZE) == 0)
            {
                is_new = 0;
                word_count[i]++;
                break;
            }
        }

        if (is_new)
        {
            strncpy(finded_word[finded_count], word, WORD_SIZE);
            word_count[finded_count] = 1;
            finded_count++;
        }
    }

    // for (size_t i = 0; i < finded_count; i++)
    // {
    //     printf("%s %d\n", finded_word[i], word_count[i]);
    // }
    return finded_count;
}
