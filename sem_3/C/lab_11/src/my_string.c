#include "stdio.h"
#include <math.h>
#include <stdarg.h>

#include "my_string.h"

#include <limits.h>

// Длина строки
size_t my_strlen(const char *str)
{
    size_t i = 0;
    while (str[i] != '\0')
        i++;

    return i;
}

// Сложение строк
char *my_strncat(char *destptr, char *srcptr, size_t num)
{
    size_t dest_len = my_strlen(destptr);
    size_t i;
    
    for (i = 0; i < num && srcptr[i] != '\0'; i++)
    {
        destptr[dest_len + i] = srcptr[i];
    }
    destptr[dest_len + i] = '\0';
    
    return destptr;
}

void reverse_str(char *str)
{
    size_t len = my_strlen(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        char tmp_char = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp_char;
    }
}

// перевод числа из 10-й СС в 16-ю
void llint_to_hex(char *str_num, unsigned long long num)
{
    if (!num)
    {
        str_num[0] = '0';
        str_num[1] = '\0';
        return;
    }

    size_t i = 0;
    int cur_digit;
    char start_pos;

    // заполнение строки остатками от деления
    for (; i < MAX_HEX_NUM_LEN - 1 && num; i++, num /= SYSTEM_BASE)
    {
        cur_digit = num % SYSTEM_BASE;
        if (cur_digit < 10)
        {
            start_pos = '0';
        }
        else
        {
            start_pos = 'a';
            cur_digit -= 10;
        }

        str_num[i] = start_pos + cur_digit;
    }
    str_num[i] = '\0';

    // разворот строки
    reverse_str(str_num);
}

// Формирование строки длины n - 1 символов, с форматированием
int my_snprintf(char *s, size_t n, const char *format, ...)
{
    va_list lst;
    va_start(lst, format);
    
    size_t s_len = 0;
    int max_len = 0;
    
    for (size_t i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%' && format[i + 1] == '\0')
        {
            max_len++;
            if (s != NULL && s_len < n - 1)
                s[s_len++] = '%';
            continue;
        }
        if (format[i] == '%')
        {
            // Обработка спецификаторов
            if (format[i + 1] == 's')
            {
                char *arg_str = va_arg(lst, char *);
                if (arg_str == NULL)
                    arg_str = "(null)";
                size_t arg_len = my_strlen(arg_str);
                max_len += (int)arg_len;
                if (s != NULL && s_len < n - 1)
                {
                    size_t copy_len = arg_len;
                    if (s_len + copy_len >= n)
                        copy_len = n - s_len - 1;
                    
                    for (size_t j = 0; j < copy_len; j++)
                        s[s_len + j] = arg_str[j];
                    
                    s_len += copy_len;
                }
                i++;
            }
            else if (format[i + 1] != '\0' && format[i + 2] != '\0' && format[i + 3] != '\0' && format[i + 1] == 'l' && format[i + 2] == 'l' && format[i + 3] == 'x')
            {
                unsigned long long arg_llint = va_arg(lst, unsigned long long);
                char hex_tmp_str[MAX_HEX_NUM_LEN];
                llint_to_hex(hex_tmp_str, arg_llint);
                size_t arg_len = my_strlen(hex_tmp_str);
                max_len += (int)arg_len;
            
                if (s != NULL && s_len < n - 1)
                {
                    size_t copy_len = arg_len;
                    if (s_len + copy_len >= n)
                        copy_len = n - s_len - 1;
                    
                    for (size_t j = 0; j < copy_len; j++)
                        s[s_len + j] = hex_tmp_str[j];
                    
                    s_len += copy_len;
                }
                i += 3;
            }
            else
            {
                max_len++;
                if (s != NULL && s_len < n - 1)
                    s[s_len++] = '%';

                if (format[i + 1] != '\0')
                {
                    max_len++;
                    if (s != NULL && s_len < n - 1)
                        s[s_len++] = format[i + 1];
                    i++;
                }
            }
        }
        else
        {
            max_len++;
            if (s != NULL && s_len + 1 < n)
            {
                s[s_len] = format[i];
                s_len++;
            }
        }
    }
    
    if (s != NULL && n > 0)
        s[s_len] = '\0';
    
    va_end(lst);
    return max_len;
}

// #include <limits.h>
// int main(void)
// {
//     // #define STR_LEN 128
//     // char a_str[STR_LEN];
//     // char b_str[STR_LEN];

//     // size_t a_n = my_snprintf(a_str, STR_LEN, "%llx", LLONG_MIN);
//     // size_t b_n = snprintf(b_str, STR_LEN, "%llx", LLONG_MIN);

//     // size_t a_n = my_snprintf(a_str, STR_LEN, "%llx", -18ll);
//     // size_t b_n = snprintf(b_str, STR_LEN, "%llx", -18ll);

//     // #undef STR_LEN

//     // printf("n = %lu | %s\n", a_n, a_str);
//     // printf("n = %lu | %s\n", b_n, b_str);

//     // long long max = 10;
//     // long long min = -10;
//     // printf("max: %llx\nmin: %llx\n", ~(max - 1), min);
//     // printf("max: %lld\nmin: %lld\n", max, min);

//         #define STR_LEN 128
//     char a_str[STR_LEN];
//     char b_str[STR_LEN];

//     size_t a_n = my_snprintf(a_str, STR_LEN, "some %zr text");
//     size_t b_n = snprintf(b_str, STR_LEN, "some %zr text");

//     #undef STR_LEN 

//     printf("n = %lu | %s\n", a_n, a_str);
//     printf("n = %lu | %s\n", b_n, b_str);
// }
