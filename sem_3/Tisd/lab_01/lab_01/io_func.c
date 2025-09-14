#include <stdio.h>
#include "large_num_struct.h"
#include <ctype.h>
#include <string.h>
#include "io_func.h"
#include "errors_code.h"


#define OK 0

#define BUFFER_SIZE 128

int input_large_num(large_num_t *num, NUMBER_TYPE t)
{
    char buffer[BUFFER_SIZE], clear_str[STR_INPUT_LEN + 1];
    int rc;
    
    rc = input_str(buffer, STR_INPUT_LEN);
    if (rc)
        return rc;

    remove_spaces(buffer, clear_str);
    rc = str_is_valid(clear_str, t);
    
    if (rc)
        return rc;

    str_to_large_num(clear_str, num);

    return OK;
}

int input_str(char *str, size_t max_len)
{
    if (fgets(str, max_len, stdin) == NULL)
        return INPUT_ERROR;
    if (strlen(str) >= max_len)
        return OVERFLOW_STR;
    
    return OK;
}

int str_is_valid(char *str, NUMBER_TYPE type)
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
    if (*str == '.' && type == INT)
    {
        return INVALID_NUMBER;
    }
    else if (*str == '.')
    {
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

void str_to_large_num(char *str, large_num_t *large_num)
{
    large_num->mantissa.len = 0;
    large_num->exponent = 0;
    
    if (*str == '-')
        large_num->sign = true;
    else
        large_num->sign = false;
    
    char *start_n = str, *end_n = str, *dot = NULL, *start_exp;
    while (*end_n && strchr("Ee", *end_n) == NULL)
    {
        if (strchr("-+0.", *start_n))
            start_n++;
        if (*end_n == '.')
            dot = end_n;
        
        end_n++;
    }
    start_exp = *end_n ? end_n + 1: end_n;
    end_n--;
    // обрезание нулей в конце числа
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
    large_num->exponent += strtol(start_exp, &str, 10);
    
    // заполнение мантиссы
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
    printf("e%d\n", num->exponent);
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
