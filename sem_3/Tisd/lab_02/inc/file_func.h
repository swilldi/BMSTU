#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#include "enums.h"
#include "structs.h"
#include <stdio.h>
#define BUFF_LEN 256

int read_str(FILE *f, char *str, size_t max_len);
int read_car(FILE *f, car_t *car);
int read_cars(FILE *f, car_t **car_table, size_t *len);
// void read_item(FILE *f);
int set_car_value(car_t *car, car_fields field, char *value);
bool is_empty(FILE *f);
int open_file(FILE **f, char *path);
size_t count_items(FILE *f);



#endif
