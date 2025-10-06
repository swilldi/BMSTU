#include "arr_func.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    *pb_dst = NULL;

    // поиск последнего не отрицательного элемента
    int *p_last_neg = (int *)pe_src;
    for (int *pcur = (int *)pb_src; pcur < pe_src; pcur++)
        if (*pcur < 0)
            p_last_neg = pcur + 1;

    // выделение памяти
    size_t count = p_last_neg - pb_src;
    *pb_dst = malloc(sizeof(int) * count);
    if (*pb_dst == NULL)
        return MALLOC_ERROR;
    *pe_dst = *pb_dst + count;

    // копирование элементов в новый массив
    for (int *pc_src = (int *)pb_src, *pc_dst = *pb_dst; pc_src < p_last_neg; pc_src++, pc_dst++)
        *pc_dst = *pc_src;

    return OK;
}

// что-то типо присваивания динамических выделего массива
void rename_arr(int **p_oab, int **p_oae, int **p_nab, int **p_nae)
{
    free(*p_oab);
    *p_oab = *p_nab;
    *p_oae = *p_nae;

    *p_nab = NULL;
    *p_nae = NULL;
}

bool arr_is_empty(int *pd, int *pe)
{
    return pd != pe;
}
