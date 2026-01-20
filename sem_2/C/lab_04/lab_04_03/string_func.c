#include "string_func.h"
#include "string_info.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// удалаяет все последующие вхождения первого символа (в задании буквы, короче пока так, что если поменяю)
void remove_first(char word[], char new_word[])
{
    size_t new_len = 0, old_len = strlen(word);
    char first_char = word[0];

    for (size_t i = 0; i < old_len; i++)
    {
        if (word[i] != first_char || i == 0)
        {
            new_word[new_len] = word[i];
            new_len++;
        }
    }
    new_word[new_len] = '\0';
}

int str_to_words(char str[], char words[][WORD_SIZE], size_t *count)
{
    *count = 0;
    char *word = strtok(str, SEPARATORS);
    while (word)
    {
        // printf("%s ", word);
        (*count)++;
        if (strlen(word) >= WORD_SIZE)
        {
            return 1;
        }

        word[strlen(word)] = '\0';

        strcpy(words[*count - 1], word);
        word = strtok(NULL, SEPARATORS);
        // printf("%s ", word);
    }
    // printf("|%lu", *count);
    return 0;
}

void new_str_generate(char words[][WORD_SIZE], size_t count, char new_str[])
{
    char last_word[WORD_SIZE];
    strcpy(last_word, words[count - 1]);
    // printf("%s\n", last_word);

    short int is_first_word = 1;

    new_str[0] = '\0';
    for (int i = (int)count - 2; i >= 0; i--)
    {
        char current_word[WORD_SIZE];
        strcpy(current_word, words[i]);

        if (strcmp(current_word, last_word) == 0)
        {
            continue;
        }

        char new_word[WORD_SIZE];
        remove_first(current_word, new_word);

        if (!is_first_word)
        {
            strcat(new_str, " ");
        }
        else
        {
            is_first_word = 0;
        }

        strcat(new_str, new_word);
    }
}
