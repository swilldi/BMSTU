#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_func.h"
#include "output_func.h"
#include "test.h"
#include "sort.h"
#include "file_func.h"
#include "table_func.h"

// сортировка по цене
int main(void)
{
    FILE *f = NULL;
    command_t cmd = 1;
    bool running = true;
    int rc = 0;
    char buff[BUFF_LEN];
    
    car_t *car_table = NULL;
    car_t *car_filtered_table = NULL;
    key_value_t *key_table = NULL;
    size_t len, max_len, len_filtered = 0;
    
    car_filter filter;
    car_t new_car;
    double price;

    #ifndef FUNC_OUT
    print_command_list();
    #endif

    while (running)
    {    
        if (cmd != EXIT)
        {
            #ifndef FUNC_OUT
            printf("Введите номер команды: ");
            #endif

            rc = input_command(&cmd);
        }
            
        if (rc != OK)
            cmd = EXIT;
        
        if (cmd != EXIT && cmd < CMP_TABLE_METHOD && f == NULL)
        {
            #ifndef FUNC_OUT
            printf("Введите путь к файлу: ");
            #endif

            rc = input_str(buff, BUFF_LEN - 2);
            if (rc != OK)
            {
                print_error_msg(rc);
                return rc;
            }

            rc = open_file(&f, buff);
            if (rc != OK)
            {
                print_error_msg(rc);
                return rc;
            }

            rc = read_cars(f, &car_table, &len);
            if (rc != OK)
            {
                print_error_msg(rc);
                return rc;
            }
            max_len = len;
        }
            
        
        switch (cmd)
        {
        case ADD_NEW_FIELD:            
            rc = input_car(&new_car);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            add_car(&car_table, &len, &max_len, &new_car);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            #ifndef FUNC_OUT
            printf("Машина добавлена\n");
            #endif

            break;
        case REMOVE_FIELD:

            #ifndef FUNC_OUT
            printf("Entry price: ");
            #endif

            rc = input_double(&price, PRISE_MAX);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }
            rc = remove_car(car_table, &len, price);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            #ifndef FUNC_OUT
            printf("Машина удалена\n");
            #endif

            break;
        case NOT_SORT_TABLE:
            print_cars(car_table, len);
            break;

        case SEARCH:
            rc = input_filter(&filter);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            car_filtered_table = malloc(len * sizeof(car_t));
            if (car_filtered_table == NULL)
            {
                rc = DINAMIC_MEMORRY_ERROR;
                break;
            }


            search_by_brand_prise(car_table, len, car_filtered_table, &len_filtered, &filter);
            print_cars(car_filtered_table, len_filtered);

            free(car_filtered_table);
            car_filtered_table = NULL;
            break;
        case TABLE_KEY:
            if (key_table != NULL)
            {
                free(key_table);
                key_table = NULL;
            }

            rc = get_table_key(car_table, &key_table, len);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            rc = shaker_sort(key_table, len, sizeof(key_value_t), cmp_car_prise_by_key);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            print_keys_table(key_table, len);
            break;
        case TABLE_CAR:
            rc = shaker_sort(car_table, len, sizeof(car_t), cmp_car_prise);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }
            print_cars(car_table, len);
            break;
        case TABLE_CAR_BY_KEY:
        if (key_table != NULL)
            {
                free(key_table);
                key_table = NULL;
            }

            rc = get_table_key(car_table, &key_table, len);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }
            
            rc = shaker_sort(key_table, len, sizeof(key_value_t), cmp_car_prise_by_key);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            print_cars_table_by_key_table(car_table, key_table, len);
            break;
        case CMP_TABLE_METHOD:
            
            printf("SHAKER\n");
            rc = test_table(shaker_sort);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            printf("BUMBLE\n");
            rc = test_table(quick_sort);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            break;
        case CMP_SORT:
            printf("TABLE\n");
            rc = test_sort(test);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            printf("KEY\n");
            rc = test_sort(test_by_key);
            if (rc != OK)
            {
                cmd = EXIT;
                break;
            }

            break;

        case EXIT:
            running = false;
            break;
        }
    }
    
    if (f != NULL)
    {
        fclose(f);
        f = NULL;
    }
        
    if (car_table != NULL)
    {
        free(car_table);
        car_table = NULL;
    } 
    
    if (key_table != NULL)
    {
        free(key_table);
        key_table = NULL;
    }

    if (rc != OK)
    {
        #ifndef FUNC_OUT
        print_error_msg(rc);
        #endif

        return rc;   
    }

    return OK;
}

