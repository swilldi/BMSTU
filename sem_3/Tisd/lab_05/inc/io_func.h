#ifndef IO_FUNC_H__
#define IO_FUNC_H__

#include "exit_code.h"
#include "queue.h"

#define BUFFER_LEN 128

error input_cmd(int *cmd, int max_value);
error input_value(q_type *value);
void print_err_msg(error rc);
void print_queue_cmd_list(void);

#endif 
