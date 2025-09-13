#include <stdio.h>
#include "large_num_struct.h"
#include <ctype.h>
#include <string.h>
#include "io_func.h"

#define INPUT_ERROR 11
#define EMPTY_STR 12
#define OVERFLOW_STR 13
#define INVALID_TYPE 14

#define INVALID_NUMBER 21
#define OVERFLOW_NUMBER 23
#define OVERFLOW_EXPONENT 23
#define OK 0

#define BUFFER_SIZE 128

int input_large_num(large_num_t *num, NUMBER_TYPE t)
{
    char buffer[BUFFER_SIZE], clear_str[STR_INPUT_LEN + 1];
    int rc;
    
    rc = input_str(buffer, STR_INPUT_LEN);
    remove_spaces(buffer, clear_str);
    switch (t)
    {
        case INT:
            return str_is_int(clear_str);
        case FLOAT:
            return str_is_float(clear_str);
        default:
            return INVALID_TYPE;
    }
}

int input_str(char *str, size_t max_len)
{
    if (fgets(str, max_len, stdin) == NULL)
        return INPUT_ERROR;
    printf("\n%lu\n", strlen(str));
    if (strlen(str) >= max_len)
        return OVERFLOW_STR;
    
    return OK;
}

int str_is_float(char *str)
{
    int digit_count = 0;
    bool has_digits = false;

    // Шаг 1: Пропускаем необязательный знак [+-]
    if (*str == '+' || *str == '-') {
        str++;
    }

    // Шаг 2: Проверка целой части мантиссы
    while (isdigit(*str)) {
        str++;
        digit_count++;
        has_digits = true;
    }

    // Шаг 3: Проверка дробной части мантиссы
    if (*str == '.') {
        str++;
        while (isdigit(*str)) {
            str++;
            digit_count++;
            has_digits = true;
        }
    }

    // Проверяем, есть ли хотя бы одна цифра в мантиссе
    if (!has_digits) {
        return INVALID_NUMBER;
    }

    // Проверяем общее количество цифр в мантиссе
    if (digit_count > DIGITS_COUNT_MAX) {
        return INVALID_NUMBER;
    }

    // Шаг 4: Проверка экспоненты [Ee]
    if (*str == 'e' || *str == 'E') {
        str++;
        int exp_digit_count = 0;

        // Пропускаем необязательный знак [+-]
        if (*str == '+' || *str == '-') {
            str++;
        }
        
        // Проверяем, есть ли хотя бы одна цифра в экспоненте
        if (!isdigit(*str)) {
            return INVALID_NUMBER;
        }

        // Проверка значения экспоненты
        while (isdigit(*str)) {
            str++;
            exp_digit_count++;
        }

        // Проверяем количество цифр в экспоненте
        if (exp_digit_count > EXPONENTA_COUNT_MAX) {
            return INVALID_NUMBER;
        }
    }
    
    // Если мы достигли конца строки и нет других символов
    if (*str == '\0') {
        return OK;
    }

    // Если остались какие-то символы, это ошибка
    return INVALID_NUMBER;
}

int str_is_int(char *str)
{
    int digit_count = 0;
    bool has_digits = false;

    if (*str == '+' || *str == '-') {
        str++;
    }

    while (isdigit(*str)) {
        str++;
        digit_count++;
        has_digits = true;
    }

    if (!has_digits) {
        return INVALID_NUMBER;
    }
    
    if (digit_count > DIGITS_COUNT_MAX) {
        return INVALID_NUMBER;
    }

    if (*str == '\0') {
        return OK;
    }

    return INVALID_NUMBER;
}

int str_to_large_num(char *str, large_num_t *large_num)
{
    large_num->mantissa.len = 0;
    large_num->exponent = 0;
    
    char *start_n = str, *end_n = str, *dot = NULL, *start_exp;
    while (*end_n && strchr("Ee", *end_n) == NULL)
    {
        if (strchr("-+0.", *start_n))
            start_n++;
        if (*end_n == '.')
            dot = end_n;
        
        end_n++;
    }
    end_n--;
    start_exp = end_n;
    while (*end_n == '0')
    {
        if (end_n == dot)
            end_n--;
        if (end_n < dot || dot == NULL)
            large_num->exponent++;
        
        end_n--;
        
    }
    
    if (dot != NULL && start_n < dot && dot < end_n)
        large_num->mantissa.len = end_n - start_n;
    else
        large_num->mantissa.len = end_n - start_n + 1;
    
    if (dot == NULL)
        large_num->exponent += large_num->mantissa.len;
    else if (start_n < dot)
        large_num->exponent += dot - start_n;
    else if (start_n > dot)
        large_num->exponent -= start_n - dot - 1;
    
    size_t i = large_num->mantissa.len - 1;
    while (start_n <= end_n)
    {
        if (*start_n == '.')
        {
            start_n++;
            continue;
        }
        
        large_num->mantissa.digits[i] = *start_n - '0';
        start_n++;
        i--;
    }
    

    return OK;
}

void remove_spaces(char *str, char *res)
{ 
    while (isspace(*str)) {
        str++;
    }

    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end--;
    }
    
    size_t len = end - str + 1;
    strncpy(res, str, len);
    res[len] = '\0';
}

void print_large_num(const large_num_t *num)
{
    if (num->sign)
        printf("-");
    printf("0.");
    for (size_t i = 1; i <= num->mantissa.len; i++)
    {
        printf("%d", num->mantissa.digits[num->mantissa.len - i]);
    }
    printf("E%d\n", num->exponent);
}

void print_large_num_info(const large_num_t *num)
{
    printf("len: %lu\n", num->mantissa.len);
    
    printf("mantissa: ");
    if (num->sign)
        printf("-");
    for (size_t i = 1; i <= num->mantissa.len; i++)
        printf("%d|", num->mantissa.digits[num->mantissa.len - i]);
    
    printf("\nexponent: %d\n", num->exponent);
}

void print_ulong_num_info(const ulong_num_t *num)
{
    printf("len: %lu\n", num->len);
    
    printf("mantissa: ");
    for (size_t i = 1; i <= num->len; i++)
        printf("%d|", num->digits[num->len - i]);
    printf("\n");
}
