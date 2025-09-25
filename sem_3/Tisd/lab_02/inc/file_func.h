#ifndef FILE_FUNC_H__
#define FILE_FUNC_H__

#include "enums.h"
#include "structs.h"

int read_str(FILE *f, char *str, size_t max_len);
int read_item(FILE *f, car_t *car);
// void read_item(FILE *f);
int set_car_value(car_t *car, car_fields *field, char *value);



#endif
