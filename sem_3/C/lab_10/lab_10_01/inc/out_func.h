#ifndef OUT_FUNC_H__
#define OUT_FUNC_H__

#include "exit_code.h"
#include <stdio.h>

void print_err_msg(error rc);

void print_int(void *value);
void print_item(void *value);
void print_item_clear(void *value);

#endif
