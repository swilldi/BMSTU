#include "table_func.h"
#include "exit_code.h"
#include <string.h>
#include <math.h>

#define ADD_car_tS 10 
#define EPS 10e-5

int add_item(car_t *table, size_t *cur_size, size_t max_size, car_t *new_car_t)
{
    if (*cur_size == max_size)
    {
        // вот это стоит уточнить, вроде бы где-то увеличивают в 2 раза, но будто бы это слишком
        table = realloc(table, sizeof(car_t) * (*cur_size + ADD_car_tS));
        if (table == NULL)
            return DINAMIC_MEMORRY_ERROR;
    }
    
    table[*cur_size] = *new_car_t;
    (*cur_size)++;

    return OK;
}

// удаление по введенной цене 
int remove_item(car_t *table, size_t *cur_size, float prise)
{
    bool field_is_finded = false;
    for (size_t i = 0; i < *cur_size; i++)
    {
        if (field_is_finded)
            table[i - 1] = table[i];
        else if (fabs(table[i].prise - prise) < EPS)
            field_is_finded = true;
    }

    (*cur_size) -= field_is_finded;
    return OK;
}

void search_items(car_t *table, size_t size, car_filter *filter, car_t *filtered_table, size_t *filtered_size)
{
    *filtered_size = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (matches_filter(&table[i], filter))
        {
            filtered_table[*filtered_size] = table[i];
            (*filtered_size)++;
        }
    }
}


bool cmp_nums(size_t v, size_t f)
{
    return f == (size_t)-1 || v == f;
}

bool matches_filter(car_t *car, car_filter *filter)
{
    if (!(filter->brend == NULL || strcmp(car->brend, filter->brend) == 0))
        return false;
    if (!cmp_nums(car->country, filter->country))
        return false;
    
    if (car->country != RUSSIA && !(car->servies == filter->servies))
        return false;
    
    if (!(filter->min_prise <= car->prise && car->prise <= filter->max_prise))
        return false;

    if (!(filter->color == NULL || strcmp(car->color, filter->color) == 0))
        return false;
    
    if (car->is_new != filter->is_new)
        return false;
    
    if (car->is_new)
    {
        if (!cmp_nums(car->info.n.warranty, filter->info.n.warranty))
            return false;
    }
    else
    {
        used_car_info c = car->info.u, f = filter->info.u;
        if (!cmp_nums(c.year, f.year))
            return false;
        if (!cmp_nums(c.mileage, f.mileage))
            return false;
        if (!cmp_nums(c.owners, f.owners))
            return false;
        if (!cmp_nums(c.repairing, f.repairing))
            return false;
    }
    
    return true;
    
}

void get_table_key(car_t *table, key_value_t *key_table, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        key_table[i].index = i;
        key_table[i].value.num_f = table[i].prise;
    }
}
