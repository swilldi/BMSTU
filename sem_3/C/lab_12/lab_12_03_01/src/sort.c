#include "sort.h"

int mysort(void *pbeg, size_t count, size_t size, comparator_t cmp)
{
    void *pend = (char *)pbeg + count * size;
    for (char *ptop = (char *)pend, *pbottom = (char *)pbeg; pbottom <= ptop;)
    {
        for (char *pprev = (char *)pbeg; pprev < ptop - size; pprev += size)
        {
            if (cmp(pprev, pprev + size) > 0)
            {
                if (swap(pprev, pprev + size, size) != OK)
                    return MALLOC_ERROR;
            }
        }
        ptop -= size;

        if (ptop <= pbottom)
            break;

        for (char *pnext = ptop - size; pnext > pbottom; pnext -= size)
        {
            if (cmp(pnext - size, pnext) > 0)
            {
                if (swap(pnext - size, pnext, size) != OK)
                    return MALLOC_ERROR;
            }
        }
        pbottom += size;
    }
    return OK;
}


int swap(void *a, void *b, size_t size)
{
    char *tmp = malloc(size);
    if (tmp == NULL)
        return MALLOC_ERROR;

    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
    return OK;
}

int cmp_int(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return *pa - *pb > 0 ? 1 : 0;
}

int cmp_double(const void *a, const void *b)
{
    double *pa = (double *)a;
    double *pb = (double *)b;
    return *pa - *pb > 0 ? 1 : 0;
}

int cmp_str(const void *a, const void *b)
{
    char *pa = (char *)a;
    char *pb = (char *)b;
    return strcmp(pa, pb) > 0 ? 1 : 0;
}
