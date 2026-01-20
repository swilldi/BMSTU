#include "item_struct.h"
#include <stdlib.h>
#define MAX_COUNT_ITEM 256

void sort_items(item_t arr[], size_t n)
{
    if (n == 0)
    {
        return;
    }

    item_t max, cur;
    size_t ind_max;

    for (size_t i = 0; i < n - 1; i++)
    {
        max = arr[i];
        ind_max = i;
        for (size_t j = i + 1; j < n; j++)
        {
            cur = arr[j];

            if (cur.prise > max.prise || (cur.prise == max.prise && cur.count > max.count))
            {
                max = cur;
                ind_max = j;
            }
        }

        if (i != ind_max)
        {
            item_t memory_item = arr[i];
            arr[i] = max;
            arr[ind_max] = memory_item;
        }
    }
}

void insert_data(item_t arr[], size_t n, item_t new_item)
{
    if (n == 0)
    {
        arr[0] = new_item;
        return;
    }

    // Находим позицию для вставки
    size_t pos = n;
    for (size_t i = 0; i < n; i++)
    {
        if (new_item.prise > arr[i].prise || (new_item.prise == arr[i].prise && new_item.count > arr[i].count))
        {
            pos = i;
            break;
        }
    }

    if (n < MAX_COUNT_ITEM)
    {
        for (size_t i = n; i > pos; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[pos] = new_item;
    }
}
