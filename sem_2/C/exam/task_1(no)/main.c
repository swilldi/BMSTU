#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "func.h"


#define STR_LEN 33
#define NUMS_COUNT 16
#define SEPARATORS "\t "


int main(void)
{
    char str[STR_LEN + 1];
    int nums[NUMS_COUNT];
    size_t count;
    input_str(str);
    get_numbers(str, nums, &count);
}




// int is_num(char *str)
// {
//     char symbol = str[0];
//     while (symbol != '\n')
//     {
        
//     }
// }

// int char_to_digit(char symbol)
// {
//     return (int)(symbol - '0');
    
// }
