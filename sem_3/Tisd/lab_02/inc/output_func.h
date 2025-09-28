#ifndef OUTPUT_FUNC_H__
#define OUTPUT_FUNC_H__

#include "structs.h"
#include <stdio.h>
#include <string.h>

#define SEPARATOR_LINE "|-------------------------------------------------------------------------------------------------------------------------------|\n"
#define SEPARATOR_LINE_SPACE "|                                                                                                                               |\n"
#define SEPARATOR_LINE_KEY "|------------------------------|\n"

void print_car(car_t *car, size_t);
void print_cars(car_t *car_table, size_t len);

void print_key_table_value(key_value_t *key);
void print_keys_table(key_value_t *key_table, size_t len);
void print_cars_table_by_key_table(car_t *car_table, key_value_t *key_table, size_t len);

void print_header(void);
void print_header_key_table(void);

void print_command_list(void);
void print_error_msg(int code);


#endif
