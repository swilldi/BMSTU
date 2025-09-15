#include <stdio.h>
#include "math_func.h"
#include "large_num_struct.h"
#include "io_func.h"
#include "errors_code.h"

void print_user_info(void)
{
    // printf("Max count of digits in mantissa: %d\nMax count of digits in exponent: %d\n", DIGITS_COUNT_MAX, EXPONENTA_COUNT_MAX);
}

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
            sprintf(msg, "string is too large (more 127 symbols");
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


int main(void)
{
    large_num_t a, b, res;
    int rc;
   
    print_user_info();

    printf("Entry dividend: ");
    rc = input_large_num(&a, INT);
    if (rc)
    {
        print_error_message(rc);
        return rc;
    }
    
    printf("Entry divider: ");
    rc = input_large_num(&b, FLOAT);
    if (rc)
    {
        print_error_message(rc);
        return rc;
    }
    
    rc = large_num_divide(&a, &b, &res);
    if (rc)
    {
        print_error_message(rc);
        return rc;
    }
    
    print_large_num(&res);
}

