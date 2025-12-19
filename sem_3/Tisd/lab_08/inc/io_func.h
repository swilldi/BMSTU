#ifndef IO_FUNC_H__
#define IO_FUNC_H__

#include <stdio.h>
#include "io_func.h"
#define SEPARATOR_LINE "========================================================\n"
void print_err_msg(int rc);
int pos_int_read(FILE *f, int *num, int *max_value);
int pos_int_input(int *num, int *max_value);
int cmd_input(int *cmd, int max_cmd_value);
void print_cmd_list(void);
void print_cmd_list_emu(void);
int intput_vertices(int *from_vert, int *to_vert, int *value);
int intput_vertices_no_value(int *from_vert, int *to_vert);
int read_vertices(char *str, int *from_vert, int *to_vert, int *value);

#endif
