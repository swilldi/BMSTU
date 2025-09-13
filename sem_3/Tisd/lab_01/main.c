#include <stdio.h>
#include "math_func.h"
#include "large_num_struct.h"
#include "io_func.h"

void print_interfare_degub(void)
{
    printf("Digits: %d\nExponenta: %d\n", DIGITS_COUNT_MAX, EXPONENTA_COUNT_MAX);
    printf("Entry number: ");
}


#define OK 0

int main(void)
{
//    large_num_t a, b, res;
    
    
//    char str[DIGITS_COUNT_MAX + DIGITS_COUNT_MAX + 2];
//    char *clear_str;
//    
//    if (fgets(str, DIGITS_COUNT_MAX + 1, stdin) == NULL)
//        return 1;
//    if (!str_is_float(str))
//        return 2;
//    clear_str = remove_spaces(str);
//    
//    str_to_large_num(clear_str, &res);
    
    
//    large_num_divide(&a, &b, &res);

//    print_large_num(&res);
    
//    large_num_t a;
//    int rc;
//    
//    print_interfare_degub();
//    rc = input_large_num(&a, FLOAT);
//    printf("is valid: %s\n", rc == OK ? "YES" : "NO");
    large_num_t a = {.exponent = 2, .mantissa = { .digits = { 1 }, .len = 2 }, .sign = true};
    large_num_t b = {.exponent = 1, .mantissa = { .digits = { 3 }, .len = 1 }, .sign = false};
    large_num_t res;
    large_num_divide(&a, &b, &res);
    
    print_large_num(&res);
}

