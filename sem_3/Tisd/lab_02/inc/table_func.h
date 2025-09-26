#ifndef TABLE_FUNC_H__
#define TABLE_FUNC_H__


#include "structs.h"
#include "table_func.h"
#include "exit_code.h"
#include <string.h>
#include <math.h>


int add_car(car_t **table, size_t *cur_size, size_t *max_size, car_t *new_car_t);
// удаление по введенной цене 
int remove_car(car_t *table, size_t *cur_size, float prise);
bool cmp_nums(size_t v, size_t f);
bool matches_filter(car_t *car, car_filter *filter);
int get_table_key(car_t *table, key_value_t **key_table, size_t size);
void search_by_brand_prise(car_t *car_table, size_t len, car_t *table_filtered, size_t *len_filtered, car_filter *filter);
#endif
