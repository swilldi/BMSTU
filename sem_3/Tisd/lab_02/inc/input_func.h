#ifndef INPUT_FUNC_H__
#define INPUT_FUNC_H__

#include "structs.h"
#include "enums.h"
#include "file_func.h"

typedef union 
{
    int i;
    double f;
} buff_num_t;

bool is_space(char *str);
int input_str(char *str, size_t max_len);
int input_int(int *num, size_t max_value);
int input_double(double *num, double max_value);
int input_car(car_t *car);
int input_filter(car_filter *filter);
void print_header(void);
void print_header_key_table(void);
int input_command(command_t *command);

#endif
