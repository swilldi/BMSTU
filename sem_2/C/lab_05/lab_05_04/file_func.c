#include "file_func.h"
#include "errors_code.h"
#include "item_struct.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_number(char *str)
{
    int i = 0;
    while (str[i] != '\0' && str[i] != '\n')
    {
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int read_file(FILE *f, item_t *arr, size_t *item_count)
{
    int field_type = 0;
    uint32_t num;
    *item_count = 0;
    char value[32];

    while (fgets(value, sizeof(value), f) != NULL)
    {
        if (value[0] == '\n')
            continue;

        value[strcspn(value, "\n\t")] = '\0';
        switch (field_type)
        {
            case 0:
                if (strlen(value) > 30)
                    return 1;
                strcpy(arr[*item_count].label, value);
                break;
            case 1:
                strcpy(arr[*item_count].producer, value);
                if (strlen(value) > 15)
                    return 1;
                break;
            case 2:
                if (!is_number(value))
                    return INVALID_CONTENT;

                num = atol(value);
                arr[*item_count].prise = num;
                break;
            case 3:
                if (!is_number(value))
                    return INVALID_CONTENT;

                num = atol(value);
                arr[*item_count].count = num;
                break;
        }

        // сохранение в массив
        if (field_type == 3)
            (*item_count)++;

        field_type = (field_type + 1) % 4;
    }
    // printf("\n%zu\n", *item_count);
    if (field_type != 0)
        return 2;
    else
        return OK;
}

void write_file(FILE *f, item_t arr[], size_t n)
{
    rewind(f);
    item_t item;
    for (size_t i = 0; i < n; i++)
    {
        item = arr[i];
        fprintf(f, "%s\n%s\n%u\n%u\n", item.label, item.producer, item.prise, item.count);
    }
}
