#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "file_func.h"
#include "table_func.h"
#include "sort.h"
#include <string.h>
#include "input_func.h"
#include "output_func.h"
#include "test.h"


#define COMMAND_MAX 8

typedef enum 
{
    EXIT,
    ADD_NEW_FIELD,
    REMOVE_FIELD,
    SEARCH,
    TABLE_KEY,
    TABLE_CAR,
    TABLE_CAR_BY_KEY,
    CMP_TABLE_METHOD,
    CMP_SORT
} command_t;

void print_command_list(void)
{
    printf(
        "1. Добавить запись в конец таблицы\n"
        "2. Удалить запись из таблицы\n"
        "3. Выполнить поиск в диапазоне цен\n"
        "4. Вывод отсортированной таблицы ключей (исходная таблица не изменяется)\n"
        "5. Вывод отсортированной таблицы (сортируется сама таблица)\n"
        "6. Вывод отсортированной таблицы (по отсортированной таблице ключей)\n"
        "7. Сравнить эффективность обработки исходной таблицы и таблицы ключей\n"
        "8. Сравнить алгоритм сортировки \"Пузырек\" и \"Шейкер\"\n"
        "0. Выйти\n"
    );
}









int input_command(command_t *command)
{
    printf("Entry command: ");
    if (scanf("%d", command) != 1)
        return INPUT_ERROR;
    if (*command > COMMAND_MAX || *command < 0)
        return INVALID_RANGE_COMMAND;
    
    return OK;
}


void print_error_msg(int code)
{
    switch (code)
    {
        case FILE_NOT_SELECTED:
            printf("file not selected\n");
            return;
        case FILE_IS_EMPTY:
            printf("file is empty\n");
            return;
        case ERROR_OPEN_FILE:
            printf("error with open file\n");
            return;
        case DINAMIC_MEMORRY_ERROR:
            printf("error with dinamic memory\n");
            return;
        case NUM_NOT_IN_RANGE:
            printf("number not in range\n");
            return;
        case INVALID_BOOL_FIELD:
            printf("invalid bool field in file\n");
            return;
        case INVALID_VALUE_IN_FIELD:
            printf("invalid value field in file\n");
            return;
        case NOT_FOUND_FIELD:
            printf("not found field\n");
            return;
        case INPUT_ERROR:
            printf("input error\n");
            return;
        case INVALID_RANGE_COMMAND:
            printf("invalid number of command\n");
            return;
    }
}





// сортировка по цене
int main(void)
{
    command_t cmd = 1;
    int rc = 0;
    char buff[BUFF_LEN];
    size_t len, max_len;
    double price;
    FILE *f = NULL;

    car_t *car_table = NULL;
    key_value_t *key_table = NULL;

    bool running = true;
    car_t *car_filtered_table = NULL;
    size_t len_filtered = 0;            
    car_filter filter;
    car_t new_car;

    

    print_command_list();

    printf("Введите путь к файлу: ");
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

    while (running)
    {
        if (rc != OK)
            cmd = EXIT;
            
        if (cmd != EXIT)
            rc = input_command(&cmd);
            
        
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

            printf("New car added\n");
            break;
        case REMOVE_FIELD:

            printf("Entry price: ");
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

            printf("Car deleted\n");
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
            rc = get_table_key(car_table, &key_table, len);
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
            }

            printf("BUMBLE\n");
            rc = test_table(bumble_sort);
            if (rc != OK)
            {
                cmd = EXIT;
            }

            break;
        case CMP_SORT:
            printf("TABLE\n");
            rc = test_sort(test);
            if (rc != OK)
            {
                cmd = EXIT;
            }

            printf("KEY\n");
            rc = test_sort(test_by_key);
            if (rc != OK)
            {
                cmd = EXIT;
            }

            break;

        case EXIT:
            printf("Closing programm\n");
            running = false;
            
            free(car_table);
            car_table = NULL;
            free(key_table);
            key_table = NULL;
            break;
        }
    }
    
    if (rc != OK)
    {
        print_error_msg(rc);
        return rc;   
    }

    return OK;
}

