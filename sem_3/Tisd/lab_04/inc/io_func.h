#ifndef IO_FUNC_H__
#define IO_FUNC_H__

#include "exit_code.h"
#include "stack_type.h"

error input_str(str_t str, FILE *f);
void print_work_mode_info(void);
void print_type_stack_info(void);
void print_cmd_list(void);
error input_cmd(int *cmd, int upper_limit);
void print_err_msg(error code);


#endif
