/*
определить количество локальных максимумов последовательности.
Чисто строго больше предыдущего и следующего. Первое и последнее числа не локальные максимумы
*/

#include "funcs.h"
#include "exit_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int local_max(FILE *f, int *count)
{
    int num_1, num_2, num_3;
    *count = 0;

    // обработка первых трех чисел
    if (fscanf(f, "%d", &num_1) != 1)
        return NUMBERS_TOO_FEW;

    if (fscanf(f, "%d", &num_2) != 1)
        return NUMBERS_TOO_FEW;

    if (fscanf(f, "%d", &num_3) != 1)
        return NUMBERS_TOO_FEW;

    // if (num_1 < num_2 && num_3 < num_2)
    //     (*count)++;

    // обработка оставшихся чисел
    do
    {
        if (num_1 < num_2 && num_3 < num_2)
            (*count)++;

        num_1 = num_2;
        num_2 = num_3;
    } while (fscanf(f, "%d", &num_3) == 1);

    return OK;
}
