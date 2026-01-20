#include "cmp_func.h"
#include "item.h"
#include <math.h>
#include <string.h>

int cmp_int(void *a, void *b)
{
    int *int_a = a;
    int *int_b = b;
    return *int_a - *int_b;
}

int cmp_item_by_title(void *a, void *b)
{
    item_t *item_a = a;
    item_t *item_b = b;
    return strcmp(item_a->title, item_b->title);
}

int cmp_item_by_prise(void *a, void *b)
{
    item_t *item_a = a;
    item_t *item_b = b;
    return item_a->prise - item_b->prise;
}

int cmp_item_by_weight(void *a, void *b)
{
    item_t *item_a = a;
    item_t *item_b = b;
    float delta = item_a->weight - item_b->weight;

    if (fabs(delta) < 1e-6)
        return 0;
    else if (delta > 0)
        return 1;
    else
        return -1;
}
