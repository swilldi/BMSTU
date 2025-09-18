#include <stdio.h>
#include "large_num_struct.h"
#include <ctype.h>
#include <string.h>
#include "io_func.h"
#include "errors_code.h"

#define BUFFER_SIZE 128

// ввод длинного числа
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

// ввод строки
int input_str(char *str, size_t max_len)
{
    if (fgets(str, max_len, stdin) == NULL)
        return INPUT_ERROR;
    if (strlen(str) >= max_len)
        return OVERFLOW_STR;
    
    return OK;
}

// проверка строки на валидность
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
    if (!*start_n)
        start_n--;
    end_n--;
    // обрезание нулей в конце числа
    while (*end_n == '0' && end_n > start_n)
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

// вывод сообщения об ошибке, по коду ошибки
void print_error_message(int rc)
{
    char msg[128];
    
    switch (rc)
    {
        case INPUT_ERROR:
            sprintf(msg, "input error");
            break;
        case EMPTY_STR:
            sprintf(msg, "empty string");
            break;
        case OVERFLOW_STR:
            sprintf(msg, "string is too large (more 127 symbols)");
            break;
        case INVALID_TYPE:
            sprintf(msg, "invalid type of number");
            break;
        case INVALID_NUMBER:
            sprintf(msg, "number is invalid");
            break;
        case OVERFLOW_NUMBER:
            sprintf(msg, "mantissa is too large");
            break;
        case OVERFLOW_EXPONENT:
            sprintf(msg, "exponent is too large");
            break;
        case MACHINE_INF:
            sprintf(msg, "result is machine infinite");
            break;
        case MACHINE_ZERO:
            sprintf(msg, "result is machine zero");
            break;
        case DIVISION_BY_ZERO:
            sprintf(msg, "division by zero");
            break;
        default:
            sprintf(msg, "unknown error (code: %d)", rc);
            break;
    }
    
    printf("%s\n", msg);
}

// вроде так линейка
void ruler(void)
{
    for (size_t i = 0; i < 16; i++)
        printf("-");
    printf("|");
    for (size_t i = 2; i <= DIGITS_COUNT_MAX; i++)
        if (i % 10 == 0)
            printf("|");
        else
            printf("-");
    printf("\n");
}
