#include "test_funcs.h"
#include <stdio.h>
#include <string.h>

#define TEST_COUNT 33

int main(void)
{
    int result = 0;

    result += test_strpbrk();
    result += test_strspn();
    result += test_strcspn();
    result += test_strchr();
    result += test_strrchr();

    printf("%d", result);
}
