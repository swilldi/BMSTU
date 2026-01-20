#ifndef STR_FUNC_H__
#define STR_FUNC_H__
#include "string_info.h"
#include <stdio.h>

int read_line(char str[]);
int to_words(char str[], char words[STRING_SIZE / WORD_SIZE][WORD_SIZE], size_t *count);
int count_word(char words[STRING_SIZE / WORD_SIZE][WORD_SIZE], char finded_word[STRING_SIZE / WORD_SIZE][WORD_SIZE], int word_count[STRING_SIZE / WORD_SIZE], size_t count);
#endif
