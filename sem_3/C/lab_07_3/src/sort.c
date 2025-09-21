#include "sort.h"


int sort(void* pbeg, size_t count, size_t size, comparator_t cmp)
{
    void *tmp = malloc(size);
    if (tmp == NULL)
        return MALLOC_ERROR;

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

void swap(void *a, void *b, size_t size, void *tmp)
{
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

int cmp_int(const void *a, const void *b)
{
    int *pa = (int *)a;
    int *pb = (int *)b;
    return *pa - *pb;
}
