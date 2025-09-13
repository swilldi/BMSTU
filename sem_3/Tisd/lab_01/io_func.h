#include "large_num_struct.h"

#include <stdio.h>
#include "large_num_struct.h"
#include <ctype.h>
#include <string.h>

typedef enum
{
    INT,
    FLOAT
} NUMBER_TYPE;

int str_is_float(char *str);

int str_is_int(char *str);

int str_to_large_num(char *str, large_num_t *large_num);

void remove_spaces(char *str, char *res);
int input_large_num(large_num_t *num, NUMBER_TYPE t);

void print_large_num(const large_num_t *num);

void print_large_num_info(const large_num_t *num);

void print_ulong_num_info(const ulong_num_t *num);
int input_str(char *str, size_t max_len);
