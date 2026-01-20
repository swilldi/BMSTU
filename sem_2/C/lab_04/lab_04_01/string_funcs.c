#include "string_funcs.h"
#include <stdio.h>

// возвращает указатель на первый попавщийся символ в str, который содержиться в chars [-]
char *my_strpbrk(char *str, char *chars)
{
    while (*str != '\0')
    {
        char *cur_char = chars;
        while (*cur_char != '\0')
        {
            if (*str == *cur_char)
            {
                return str;
            }
            cur_char++;
        }
        str++;
    }
    return NULL;
}

// возвращает длину первой подстроки состоящей только из символов входящих в chars [-]
size_t my_strspn(char *str, char *chars)
{
    size_t len = 0, len_before = 0;
    // проход по символам строки
    while (*str != '\0')
    {
        // поиск символа в переданых символах
        char *cur_char = chars;
        while (*cur_char != '\0')
        {
            // printf("%c %c\n", *str, *cur_char);
            if (*str == *cur_char)
            {
                len++;
                break;
            }
            cur_char++;
        }

        // если длина изменилась продолжаем поиск
        if (len != len_before)
        {
            len_before = len;
            str++;
        }
        // иначе завершаем
        else
        {
            break;
        }
    }
    return len;
}

// возвращает длину первой подстроки состоящей только из символов НЕ входящих в chars [-]
size_t my_strcspn(char *str, char *chars)
{
    size_t len = 0;
    // проход по символам строки
    while (*str != '\0')
    {
        // поиск символа в переданых символах
        char *cur_char = chars;
        while (*cur_char != '\0')
        {
            // printf("%c %c\n", *str, *cur_char);
            if (*str == *cur_char)
            {
                return len;
                break;
            }
            cur_char++;
        }
        len++;
        str++;
    }
    return len;
}

// возвращает указатель на первое вхождение символа ch в строку [+]
char *my_strchr(char str[], char ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
        {
            return str;
        }
        str++;
    }
    return ch == '\0' ? str : NULL;
}

// возвращает указатель на последнее вхождение символа ch в строку [+]
char *my_strrchr(char str[], char ch)
{
    char *symbol = NULL;

    do
    {
        if (*str == ch)
        {
            symbol = str;
        }
    } while (*(str++) != '\0');
    return symbol;
}
