#ifndef STRING_FUNCS_H__
#define STRING_FUNCS_H__

#include <stdio.h>

char *my_strpbrk(char *str, char *chars);
size_t my_strspn(char *str, char *chars);
size_t my_strcspn(char *str, char *chars);
char *my_strchr(char str[], char ch);
char *my_strrchr(char str[], char ch);

#endif
