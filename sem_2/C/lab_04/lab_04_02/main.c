/*
Ввести одну строку. Для каждого слова подсчитать количество его встреч в
исходной строке. Программа должна вывести пары «слово количество-встреч».
Каждая пара выводится на отдельной строке. Слова выводятся в том порядке,
в котором они встретились в исходной строке.
*/

#include "errors.h"
#include "string_func.h"
#include "string_info.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void print_result(char words[][WORD_SIZE], int word_count[], size_t finded_count)
{
    for (size_t i = 0; i < finded_count; i++)
    {
        printf("Result: %s %d\n", words[i], word_count[i]);
    }
}

int main(void)
{
    char str[STRING_SIZE], words[STRING_SIZE / WORD_SIZE][WORD_SIZE];
    int read_res = read_line(str);
    size_t count;

    if (*str == '\0')
    {
        printf(EMPTY_STRING_MESSAGE);
        return EMPTY_STRING_ERROR;
    }

    if (read_res != 0)
    {
        printf(STRING_OWERFLOW_MESSAGE);
        return STRING_OWERFLOW_ERROR;
    }

    // printf("%s\n", str);
    if (to_words(str, words, &count) != 0)
    {
        printf(WORD_OWERFLOW_MESSAGE);
        return WORD_OWERFLOW_ERROR;
    }

    if (count < 1)
    {
        printf(EMPTY_STRING_MESSAGE);
        return EMPTY_STRING_ERROR;
    }

    // for (size_t i = 0; i < count; i++)
    // {
    //     printf("%s\n", words[i]);
    // }

    char finded_word[STRING_SIZE / WORD_SIZE][WORD_SIZE];
    int word_count[STRING_SIZE / WORD_SIZE];
    size_t finded_count = count_word(words, finded_word, word_count, count);

    if (count == 1)
    {
        return 1;
    }

    print_result(finded_word, word_count, finded_count);
}
