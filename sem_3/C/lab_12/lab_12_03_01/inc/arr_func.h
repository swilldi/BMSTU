#ifndef ARR_FUNC_H__
#define ARR_FUNC_H__

#include <stdbool.h>
#include <stdlib.h>
#include "exit_code.h"

int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst);
const int *arr_last_neg(const int *pb, const int *pe);
// что-то типо присваивания динамических выделего массива
void rename_arr(int **p_oab, int **p_oae, int **p_nab, int **p_nae);
bool arr_is_empty(const int *pd, const int *pe);
int create_arr(size_t len, int **arr_b, int **arr_e);

#endif 
