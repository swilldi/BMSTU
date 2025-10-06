#ifndef ARR_FUNC_H__
#define ARR_FUNC_H__

#include <stdbool.h>
#include <stdlib.h>
#include "exit_code.h"

bool arr_is_empty(int *pd, int *pe);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
void rename_arr(int **p_oab, int **p_oae, int **p_nab, int **p_nae);

#endif 
