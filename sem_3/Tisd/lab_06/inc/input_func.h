#ifndef INPUT_FUNC_H__
#define INPUT_FUNC_H__

#include <stdio.h>
#include "tree.h"
#include "exit_code.h"


int input_cmd(int *cmd, int max_value);
int input_str(char *str, char *msg);
int input_char(char *symbol);

#endif
