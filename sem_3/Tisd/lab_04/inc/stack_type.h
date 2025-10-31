#ifndef STACK_TYPE_H__
#define STACK_TYPE_H__

#include <stdint.h>
#define STACK_MAX_LEN 64
#define STR_MAX_LEN 64
#define str_t char*

typedef struct
{
    char (*down_p)[STR_MAX_LEN];  // Нижняя граница стека
    char (*sp)[STR_MAX_LEN];      // Текущий элемент
} my_stack_t;

typedef struct stack_list_t stack_list_t; 
struct stack_list_t
{
    stack_list_t *prev;  // Предыдущий элемент стека

    char sp[STR_MAX_LEN];                // Текущий элемент
    unsigned char ind;
};

#endif
