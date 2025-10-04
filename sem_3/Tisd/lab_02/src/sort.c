#include "sort.h"
#include "structs.h"
#include "exit_code.h"
#include <math.h>
#define EPS 10e-5


// === ШЕЙКЕР ===
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

// === БЫСТРАЯ СОРТИРОВКА ===
 char *partition(char *low, char *high, size_t size, comparator_t cmp, void *tmp)
{
    char *pivot = high;
    char *i = low - size;

    for (char *j = low; j < high; j += size) {
        if (cmp(j, pivot) < 0) {
            i += size;
            swap(i, j, size, tmp);
        }
    }
    swap(i + size, high, size, tmp);
    return i + size;
}

void quicksort(char *low, char *high, size_t size, comparator_t cmp, void *tmp)
{
    if (low >= high)
        return;

    char *pi = partition(low, high, size, cmp, tmp);

    quicksort(low, pi - size, size, cmp, tmp);
    quicksort(pi + size, high, size, cmp, tmp);
}

int quick_sort(void *pbeg, size_t count, size_t size, comparator_t cmp)
{
    if (count <= 1) 
        return 2;

    void *tmp = malloc(size);
    if (tmp == NULL)
        return DINAMIC_MEMORRY_ERROR;

    char *low = (char *)pbeg;
    char *high = (char *)pbeg + (count - 1) * size;

    quicksort(low, high, size, cmp, tmp);

    free(tmp);
    return OK;
}

// === СРАВНЕНИЯ === 
double cmp_car_prise(const void *a, const void *b)
{
    car_t *p_car_a = (car_t *)a;
    car_t *p_car_b = (car_t *)b;
    return p_car_a->prise - p_car_b->prise;
}

double cmp_car_prise_by_key(const void *a, const void *b)
{
    key_value_t *p_key_value_a = (key_value_t *)a;
    key_value_t *p_key_value_b = (key_value_t *)b;
    return p_key_value_a->value.num_f - p_key_value_b->value.num_f;
}

// === ОСТАЛЬНЫЕ ФУНКЦИИ ===
void swap(void *a, void *b, size_t size, void *tmp)
{
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}



