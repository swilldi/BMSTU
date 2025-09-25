#ifndef TABLE_FUNC_H__
#define TABLE_FUNC_H__

#include "structs.h"

#include "table_func.h"
#include "exit_code.h"
#include <string.h>
#include <math.h>

#define ADD_car_tS 10 
#define EPS 10e-5

int add_item(car_t *table, size_t *cur_size, size_t max_size, car_t *new_car_t);
// удаление по введенной цене 
int remove_item(car_t *table, size_t *cur_size, float prise);
void search_items(car_t *table, size_t size, car_filter *filter, car_t *filtered_table, size_t *filtered_size);
bool cmp_nums(size_t v, size_t f);
bool matches_filter(car_t *car, car_filter *filter);
void get_table_key(car_t *table, key_value_t *key_table, size_t size);
#endif
