#ifndef STR_FUNC_H__
#define STR_FUNC_H__

#include "stdio.h"
#include "string_info.h"
// удалаяет все последующие вхождения первого символа (в задании буквы, короче пока так, что если поменяю)
void remove_first(char word[], char new_word[]);
int str_to_words(char str[], char words[][WORD_SIZE], size_t *count);
void new_str_generate(char words[][WORD_SIZE], size_t count, char new_str[]);

#endif
