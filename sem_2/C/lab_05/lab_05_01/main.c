/*
определить количество локальных максимумов последовательности.
Чисто строго больше предыдущего и следующего. Первое и последнее числа не локальные максимумы
*/

#include "exit_code.h"
#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int count;
    if (local_max(stdin, &count) != OK)
    {
        return NUMBERS_TOO_FEW;
    }
    printf("Result: %d\n", count);
}
