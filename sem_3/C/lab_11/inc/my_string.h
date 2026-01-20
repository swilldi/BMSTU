#ifndef MY_STRING_H__
#define MY_STRING_H__

#include "stdio.h"
#include <math.h>
#include <stdarg.h>

#define MAX_HEX_NUM_LEN 32
#define SYSTEM_BASE 16

typedef enum
{
    INT,
    LLINT_16,
} number_type;

// Длина строки
size_t my_strlen(const char *str);

// Сложение строк
char *my_strncat(char *destptr, char *srcptr, size_t num);

void reverse_str(char *str);

// перевод числа из 10-й СС в 16-ю
void llint_to_hex(char *str_num, unsigned long long num);

// Сложение строки и числа

// Формирование строки длины n - 1 символов, с форматированием
int my_snprintf(char *s, size_t n, const char *format, ...);

#endif
