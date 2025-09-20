#include <stdio.h>
#include "math_func.h"
#include "large_num_struct.h"
#include "io_func.h"
#include "errors_code.h"
#include <stdio.h>


void number_info(void)
{
    printf("Divide int to float\n");
    printf("Max count of digits in mantissa: %d\nMax count of digits in exponent: %d\n", 
            DIGITS_COUNT_MAX, EXPONENTA_COUNT_MAX);
    printf("frormat input:\nInt: N, len N <= 40\nFloat: N.M[eE]+-K, len N + M <= 40, len K <= 5\n");
}

int main(void)
{
   large_num_t a, b, res;
   int rc;
    
   number_info();

   ruler();
   printf("Entry dividend: ");
   rc = input_large_num(&a, INT);
   if (rc)
   {
       print_error_message(rc);
       return rc;
   }
   
   ruler();
   printf("Entry  divider: ");
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

