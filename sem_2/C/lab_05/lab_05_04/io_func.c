#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors_code.h"
#include "item_struct.h"
#include <ctype.h>

void print_item(item_t item)
{
    printf("label: %s\nProducter: %s\nPrise: %d\nCount: %d\n\n", item.label, item.producer, item.prise, item.count);
}

int input_str(char str[], size_t max_len)
{
    if (fgets(str, max_len + 2, stdin) == NULL)
        return 1;

    size_t len = strlen(str);
    if (len > max_len)
    {
        // Очистка буфера
        return STR_OVERFLOW;
    }
    str[len - 1] = '\0';
    return OK;
}

int input_item(item_t *item)
{
    char buffer[32];

    // Ввод названия
    // printf("Введите название: ");
    int rc = input_str(buffer, sizeof(buffer) - 2);
    if (rc != OK)
        return rc;
    strcpy(item->label, buffer);

    // Ввод производителя
    // printf("Введите производителя: ");
    rc = input_str(buffer, 15);
    if (rc != OK)
        return rc;
    strcpy(item->producer, buffer);

    // ввод цены
    // printf("Введите цену: ");
    int num;
    if (scanf("%d", &num) != 1 || num < 0)
        return INVALID_CONTENT;
    item->prise = num;

    // ввод количества
    // printf("Введите количество: ");
    if (scanf("%d", &num) != 1 || num < 0)
        return INVALID_CONTENT;
    item->count = num;

    return OK;
}
