#include "sort.h"
#include "structs.h"
#include "exit_code.h"
#include <math.h>
#define EPS 10e-5

int shaker_sort(void *pbeg, size_t count, size_t size, comparator_t cmp)
{
    void *tmp = malloc(size);
    if (tmp == NULL)
        return DINAMIC_MEMORRY_ERROR;

    void *pend = (char *)pbeg + count * size;
    for (char *ptop = (char *)pend, *pbottom = (char *)pbeg; pbottom <= ptop;)
    {
        for (char *pprev = (char *)pbeg; pprev < ptop - size; pprev += size)
        {
            if (cmp(pprev, pprev + size) > 0)
                swap(pprev, pprev + size, size, tmp);
        }
        ptop -= size;

        if (ptop <= pbottom)
            break;

        for (char *pnext = ptop - size; pnext > pbottom; pnext -= size)
        {
            if (cmp(pnext - size, pnext) > 0)
                swap(pnext - size, pnext, size, tmp);
        }
        pbottom += size;
    }

    free(tmp);
    return OK;
}

int bumble_sort(void *pbeg, size_t count, size_t size, comparator_t cmp)
{
    void *tmp = malloc(size);
    if (tmp == NULL)
        return DINAMIC_MEMORRY_ERROR;

    void *pend = (char *)pbeg + count * size;
    for (char *ptop = (char *)pend; (char *)pbeg < ptop; ptop--)
    {
        for (char *pprev = (char *)pbeg; pprev < ptop - size; pprev += size)
        {
            if (cmp(pprev, pprev + size) > 0)
                swap(pprev, pprev + size, size, tmp);
        }
    }

    free(tmp);
    return OK;
}

void swap(void *a, void *b, size_t size, void *tmp)
{
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

float cmp_car_prise(const void *a, const void *b)
{
    car_t *p_car_a = (car_t *)a;
    car_t *p_car_b = (car_t *)b;
    return p_car_a->prise - p_car_b->prise;
}

float cmp_car_prise_by_key(const void *a, const void *b)
{
    key_value_t *p_key_value_a = (key_value_t *)a;
    key_value_t *p_key_value_b = (key_value_t *)b;
    return p_key_value_a->value.num_f - p_key_value_b->value.num_f;
}
