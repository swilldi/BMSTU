#include "table_func.h"
#include "exit_code.h"
#include <string.h>
#include <math.h>

#define ADD_car_tS 10 
#define EPS 10e-1

int add_car(car_t **table, size_t *cur_size, size_t *max_size, car_t *new_car_t)
{
    if (*cur_size == *max_size)
    {
        // вот это стоит уточнить, вроде бы где-то увеличивают в 2 раза, но будто бы это слишком
        (*table) = realloc((*table), sizeof(car_t) * (*cur_size) * 2);
        if ((*table) == NULL)
        {
            return DINAMIC_MEMORRY_ERROR;
        }
            
        (*max_size) *= 2;
    }
    
    (*table)[*cur_size] = *new_car_t;
    (*cur_size)++;

    return OK;
}

// удаление по введенной цене 
int remove_car(car_t *table, size_t *cur_size, double prise)
{
    bool field_is_finded = false;
    for (size_t i = 0; i < *cur_size; i++)
    {
        if (field_is_finded)
            table[i - 1] = table[i];
        else if (fabs(table[i].prise - prise) < EPS)
            field_is_finded = true;
    }
    
    if (field_is_finded)
    {
        (*cur_size) -= field_is_finded;
        return OK;
    }
    else 
    {
        return NOT_FOUND_FIELD;
    }
        
    
}

// void get_filtered_table(car_t *table, size_t size, car_filter *filter, car_t *filtered_table, size_t *filtered_size)
// {
//     *filtered_size = 0;
//     for (size_t i = 0; i < size; i++)
//     {
//         if (matches_filter(&table[i], filter))
//         {
//             filtered_table[*filtered_size] = table[i];
//             (*filtered_size)++;
//         }
//     }
// }

int get_table_key(car_t *table, key_value_t **key_table, size_t len)
{
    *key_table = (key_value_t *)malloc(len * sizeof(key_value_t));
    if (*key_table == NULL)
        return DINAMIC_MEMORRY_ERROR;

    for (size_t i = 0; i < len; i++)
    {
        (*key_table)[i].index = i;
        (*key_table)[i].value.num_f = table[i].prise;
    }

    return OK;
}

bool match_filter(car_t *car, car_filter *filter)
{
    if (strcmp(car->brend, filter->brend) != 0) 
        return false;
    
    if (filter->min_prise > car->prise && car->prise > filter->max_prise)
        return false;

    if (car->is_new)
        return false;

    if (car->info.u.owners != filter->info.u.owners)
        return false;

    if (car->info.u.repairing != filter->info.u.repairing)
        return false;

    return true;
}

void search_by_brand_prise(car_t *car_table, size_t len, car_t *table_filtered, size_t *len_filtered, car_filter *filter)
{
    car_t car;
    *len_filtered = 0;
    for (size_t i = 0; i < len; i++)
    {
        car = car_table[i];

        if (match_filter(&car, filter))
        {
            table_filtered[*len_filtered] = car;
            (*len_filtered)++;
        }
    }
}
