/*
Вариант: 2
Номер задач: 1, 3
Тип файлов: txt

О каждом товаре известны:
(a) наименование, не более 30 символов;
(b) изготовитель, не более 15 символов;
(c) цена единицы товара, сохраняемая в виде целого беззнакового в 32 бита;
(d) количество единиц товара, сохраняемое в виде целого беззнакового в 32 бита.

(1)
    // Сделать
    Сортировка по убыванию цены, если цена одинаковая по количеству

    // Результат
    Новый файл

    // Вызов
    ./app.exe st FILE_SRC FILE_DST

(3)
    // Дано
    Последовательность упорядочена.

    // Сделать
    Получить у пользователя информацию о новом товаре,
    Добавить так чтобы упорядоченость не нарушилась

    // Результат
    Измененный файл


    // Вызов
    ./app.exe at FILE
*/

// А может быть если в файле сначала правильные структуры, а потом неправильная это полностью фигня,
// а не просто не учитывать последнее

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors_code.h"
#include "file_func.h"
#include "io_func.h"
#include "item_struct.h"
#include "struct_func.h"

#define MAX_COUNT_ITEM 256

int main(int argc, char **argv)
{
    if (argc < 3)
        return ARGS_TOO_FEW;

    if (strcmp(argv[1], "st") == 0)
    {
        if (argc < 4)
            return ARGS_TOO_FEW;

        FILE *old_f = fopen(argv[2], "r");
        if (old_f == NULL)
            return FILE_OPEN_ERROR;

        FILE *new_f = fopen(argv[3], "w");

        item_t items[MAX_COUNT_ITEM] = { 0 };
        size_t count;
        read_file(old_f, items, &count);
        if (count == 0)
            return INVALID_CONTENT;
        sort_items(items, count);
        write_file(new_f, items, count);

        fclose(old_f);
        fclose(new_f);
    }
    else if (strcmp(argv[1], "at") == 0)
    {
        FILE *f = fopen(argv[2], "r");
        if (f == NULL)
            return FILE_OPEN_ERROR;

        item_t items[MAX_COUNT_ITEM] = { 0 };
        item_t new_item;
        size_t count;

        read_file(f, items, &count);
        fclose(f);

        if (count > MAX_COUNT_ITEM - 1)
            return ITEMS_OVERFLOW;

        int rc = input_item(&new_item);
        if (rc != 0)
            return rc;

        insert_data(items, count, new_item);
        count++;

        f = fopen(argv[2], "w");
        if (f == NULL)
            return FILE_OPEN_ERROR;
        write_file(f, items, count);
        fclose(f);
    }
    else if (strcmp(argv[1], "p") == 0)
    {
        FILE *f = fopen(argv[2], "r");
        if (f == NULL)
            return FILE_OPEN_ERROR;

        item_t items[MAX_COUNT_ITEM] = { 0 };
        size_t count;

        read_file(f, items, &count);
        for (size_t i = 0; i < count; i++)
            print_item(items[i]);

        fclose(f);
    }
    else
    {
        return 53;
    }
}
