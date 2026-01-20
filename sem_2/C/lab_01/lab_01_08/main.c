// Вводятся беззнаковое целое число длиной 4 байта 𝑎 и целое число 𝑛. Числа
// вводятся в десятичной системе счисления. Необходимо циклически сдвинуть
// значение переменной 𝑎 на 𝑛 позиций вправо. Результат вывести в двоичной
// системе счисления

#include <stdint.h>
#include <stdio.h>
#define INPUT_ERROR 1
#define INT_SIZE 32

void binary_print(uint32_t number)
{
    printf("Result: ");
    for (int i = INT_SIZE - 1; i >= 0; i--)
    {        
        if ((number & ((uint32_t)1 << i)))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

int main(void)
{
    uint32_t number;
    int shift;

    printf("Entry number: ");
    if (scanf("%u", &number) != 1)
    {
        printf("Error: invalid input for number\n");
        return INPUT_ERROR;
    }

    // printf("10-CC: %lu\n", number);
    // binary_print(number);

    printf("Entry n: ");
    if (scanf("%d", &shift) != 1 || shift < 0)
    {
        printf("Error: invalid input for number\n");
        return INPUT_ERROR;
    }

    // printf("%d", shift);
    if (shift >= INT_SIZE)
    {
        shift %= INT_SIZE;
    }

    if (shift != 0)
    {
        number = (number >> shift) | (number << (INT_SIZE - shift));
    }

    binary_print(number);

    return 0;
}
