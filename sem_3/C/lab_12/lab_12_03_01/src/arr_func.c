#include "arr_func.h"

int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst)
{
    if (pb_dst == pe_dst)
        return EMPTY_ARR;

    // копирование элементов в новый массив
    size_t count = pe_dst - pb_dst;
    const int *src = pb_src;
    int *dst = pb_dst;
    for (size_t i = 0; i < count && pb_src + i < pe_src; i++)
        dst[i] = src[i];

    return OK;
}

const int *arr_last_neg(const int *pb, const int *pe)
{
    // поиск последнего отрицательного элемента
    const int *last_neg_ptr = pe;
    for (int *pcur = (int *)pb; pcur < pe; pcur++)
        if (*pcur < 0)
            last_neg_ptr = pcur;
    
    return last_neg_ptr;
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

bool arr_is_empty(const int *pd, const int *pe)
{
    return pd != pe;
}

int create_arr(size_t len, int **arr_b, int **arr_e)
{
    if (*arr_b != NULL)
        return MALLOC_ERROR;

    *arr_b = malloc(sizeof(int) * len);
    if (arr_b == NULL)
        return MALLOC_ERROR;

    *arr_e = *arr_b + len;

    return OK;
}
