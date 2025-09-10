#include <stdio.h>
#include "large_num_struct.h"
#include <ctype.h>
#include <string.h>

#define EMPTY_STR 10
#define INVALID_NUMBER 11
#define OVERFLOW_NUMBER 13
#define OVERFLOW_EXPONENT 13
#define OK 0

int str_is_float(char *str)
{
    bool dot_was = false;   

    // до числа только нули или пробельные символы
    while (*str == '0' || isspace(*str))
        str++;
    
    // проверка знака и возможной точки сразу после него
    if (strchr("+-", *str) && isdigit(*(str + 1)))
        str++;
    else if (*str == '.' && isdigit(*(str + 1)))
    {
        str++;
        dot_was = true;
    }
    else if (strchr("+-", *str) && *(str + 1) == '.' && isdigit(*(str + 2)))
    {
        str += 2;
        dot_was = true;
    }
    else if (!isdigit(*str))
        return INVALID_NUMBER;

    // проверка числа
    while (!*str)
    {
        if (isdigit(*str));
        else if (*str == '.')
        {
            if (dot_was)
                return INVALID_NUMBER;
            else
                dot_was = true;
        }
        else if (strchr("Ee", *str) != NULL)
        {
            str++;
            break;
        }
        else
            return INVALID_NUMBER;

        str++;
    }
    
    // если достигли конца строки, то возвращаем значение
    if (*str)
        return OK;

    // проверка знака
    if (strchr("+-", *str) && isdigit(*(str + 1)))
        str++;
    else if (!isdigit(*str))
        return INVALID_NUMBER;

    // проверка значения экспоненты
    while (!*str)
    {
        if (!isdigit(*str))
            return INVALID_NUMBER;
        str++;
    }

    return OK;
}

int str_to_large_num(char *str, large_num_t *large_num)
{
    large_num->len = 0;
    large_num->exponent = 0;

    char *start = str, *end = str, *exp_start = str;
    // char *start = str, *end = str;
    bool dot = false;
    
    // границы мантисы
    while (strchr("-+0", *start))
        start++;
    if (*start == '.')
    {
        start++;
        while(*start == '0')
        {
            start++;
            large_num->exponent--;
        }
    }
    // начало экспоненты
    end = start;
    while (*end && strchr("Ee", *end) == NULL)
        {
            if (*end == '.')
            {
                dot = true;
            }
                
            end++;
        }
    
    if (*end)
        exp_start = end;
    
    end--;
    while (*end == '0' && end != start)
        end--;

    // знак числа
    if (*str == '-')
        large_num->sign = true;
    else
        large_num->sign = false;
    
    // запись длины числа
    large_num->len = end - start - dot + 1;

    // запись мантисы
    size_t i = end - start - dot;
    for (size_t n = 0; n <= (size_t)(end - start) ; n++)
    {
        if (isdigit(*(start + n)))
        {
            large_num->mantissa[i] = *(start + n) - '0';
            i--;
        }
        if (*(start + n) == '.')
            large_num->exponent += n;
    }

    // printf("\n%ld\n", atol(exp_start + 1));
    if (exp_start != str)
        large_num->exponent += atol(exp_start + 1);
    if (!dot)
        large_num->exponent += large_num->len;

    return OK;
}

char* remove_spaces(char *str)
{
    char *end;

    // удаление пробелов в начале
    while (isspace((*str)))
        str++;

    if (*str == '\0')
        return str;

    // удаление пробелов с конца
    end = str + strlen(str) - 1;
    while (str <= end && isspace(*end))
    {
        *end = '\0';
        end--;
    }

    return str;
}

void print_num(const large_num_t *num)
{
    if (num->sign)
        printf("-");
    printf("0.");
    for (size_t i = 1; i <= num->len; i++)
    {
        printf("%d", num->mantissa[num->len - i]);
    }
    printf("E%d\n", num->exponent);
}

void print_num_info(const large_num_t *num)
{
    printf("len: %lu\n", num->len);
    
    printf("mantissa: ");
    if (num->sign)
        printf("-");
    for (size_t i = 1; i <= num->len; i++)
        printf("%d|", num->mantissa[num->len - i]);
    
    printf("\nexponent: %d\n", num->exponent);
}
