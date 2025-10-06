#include "test.h"
#include "file_func.h"
#define PATH_LEN

#define ST_HEADER_METHOD "| count | by_table, сек | by_key, сек | by_key / by_table, %% | cars mem, b  | keys mem, b | keys / cars, %% |\n"
#define ST_HEADER_SORT   "| count |  quick, сек   | shaker, сек |   quick / shaker, %%  | cars mem, b  | keys mem, b | keys / cars, %% |\n"
#define ST_SEPARATOR     "--------+---------------+-------------+----------------------+--------------+-------------+-----------------\n"

int test(FILE *f, sort_type sort_method, double *res)
{
    clock_t start, end;
    *res = 0;
    size_t len;
    int rc;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        car_t *table = NULL;
        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        sort_method(table, len, sizeof(car_t), cmp_car_prise);
        
        if (table != NULL)
            free(table);
    }
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        car_t *table = NULL;

        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        
        start = clock();
        sort_method(table, len, sizeof(car_t), cmp_car_prise);
        end = clock();

        if (table != NULL)
            free(table);

        *res = (double)(end - start + *res) / 2;
    }

    *res /= CLOCKS_PER_SEC;
    return rc;
}

int test_by_key(FILE *f, sort_type sort_method, double *res)
{
    clock_t start, end;
    *res = 0;
    size_t len;
    int rc;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        car_t *table = NULL;
        key_value_t *table_key = NULL;

        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        rc = get_table_key(table, &table_key, len);
        if (rc != OK)
            break;
        sort_method(table_key, len, sizeof(key_value_t), cmp_car_prise_by_key);

        free(table);
        free(table_key);
    }
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        car_t *table = NULL;
        key_value_t *table_key = NULL;

        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        
        start = clock();
        rc = get_table_key(table, &table_key, len);
        if (rc != OK)
            break;
        sort_method(table_key, len, sizeof(key_value_t), cmp_car_prise_by_key);
        end = clock();

        free(table);
        free(table_key);        

        *res = (double)(end - start + *res) / 2;
    }

    *res /= CLOCKS_PER_SEC;

    return rc;
}

int get_count(int num)
{
    switch (num)
    {
    case 0:
        return 20;
    case 1:
        return 100;
    case 2:
        return 500;
    case 3:
        return 1000;
    case 4:
        return 2000;
    case 5:
        return 5000;
    case 6:
        return 10000;
    }
    return 0;
}




int test_table(sort_type sort)
{
    double res_table, res_key;
    int rc;
    char *(paths[PATH_LEN]) = {
        "./test_files/cars_dataset_20.txt",
        "./test_files/cars_dataset_100.txt",
        "./test_files/cars_dataset_500.txt",
        "./test_files/cars_dataset_1000.txt",
        "./test_files/cars_dataset_2000.txt",
        "./test_files/cars_dataset_5000.txt",
        "./test_files/cars_dataset_10000.txt"
    };

    printf(
        ST_SEPARATOR
        ST_HEADER_METHOD
        ST_SEPARATOR
    );

    for (size_t i = 0; i < sizeof(paths) / sizeof(*paths); i++)
    {
        FILE *f = NULL;
        

        rc = open_file(&f, (char *)paths[i]);
        if (rc != OK)
            return rc;

        rc = test(f, sort, &res_table);
        if (rc != OK)
            return rc;

        rc = test_by_key(f, sort, &res_key);
        if (rc != OK)
            return rc;
        
        size_t count = count_items(f);
        fclose(f);
        
        size_t cars_mem = sizeof(car_t) * count, keys_mem = sizeof(key_value_t) * count;
        double percent_time = (res_table - res_key) / res_table * 100;
        double percent_memory = (double)keys_mem / cars_mem * 100;
        
        printf("| %5lu | %13.5lf | %11.5lf | %19.2lf%% | %12lu | %11lu | %14.2lf |\n", count, res_table, res_key, percent_time, cars_mem, keys_mem, percent_memory);
    }
    printf(ST_SEPARATOR);
    return OK;
}

int test_table(void)
{
    double res_table, res_key;
    int rc;
    char *(paths[PATH_LEN]) = {
        "./test_files/cars_dataset_20.txt",
        "./test_files/cars_dataset_100.txt",
        "./test_files/cars_dataset_500.txt",
        "./test_files/cars_dataset_1000.txt",
        "./test_files/cars_dataset_2000.txt",
        "./test_files/cars_dataset_5000.txt",
        "./test_files/cars_dataset_10000.txt"
    };

    printf(
        ST_SEPARATOR
        ST_HEADER_METHOD
        ST_SEPARATOR
    );

    for (size_t i = 0; i < sizeof(paths) / sizeof(*paths); i++)
    {
        FILE *f = NULL;
        

        rc = open_file(&f, (char *)paths[i]);
        if (rc != OK)
            return rc;

        rc = test(f, shaker_sort, &res_table);
        if (rc != OK)
            return rc;

        rc = test_by_key(f, quick_sort, &res_key);
        if (rc != OK)
            return rc;
        
        size_t count = count_items(f);
        fclose(f);
        
        size_t cars_mem = sizeof(car_t) * count, keys_mem = sizeof(key_value_t) * count;
        double percent_time = (res_table - res_key) / res_table * 100;
        double percent_memory = (double)keys_mem / cars_mem * 100;
        
        printf("| %5lu | %13.5lf | %11.5lf | %19.2lf%% | %12lu | %11lu | %14.2lf |\n", count, res_table, res_key, percent_time, cars_mem, keys_mem, percent_memory);
    }
    printf(ST_SEPARATOR);
    return OK;
}


int test_sort(test_type test_f)
{
    double res_shaker, res_quick;
    int rc;
    char *(paths[PATH_LEN]) = {
        "./test_files/cars_dataset_20.txt",
        "./test_files/cars_dataset_100.txt",
        "./test_files/cars_dataset_500.txt",
        "./test_files/cars_dataset_1000.txt",
        "./test_files/cars_dataset_2000.txt",
        "./test_files/cars_dataset_5000.txt",
        "./test_files/cars_dataset_10000.txt"
    };

    printf(
        ST_SEPARATOR
        ST_HEADER_SORT
        ST_SEPARATOR
    );

    for (size_t i = 0; i < sizeof(paths) / sizeof(*paths); i++)
    {
        FILE *f = NULL;
        
        rc = open_file(&f, (char *)paths[i]);
        if (rc != OK)
            return rc;

        rc = test_f(f, shaker_sort, &res_shaker);
        if (rc != OK)
            return rc;
        rc = test_f(f, quick_sort, &res_quick);
        if (rc != OK)
            return rc;

        size_t count = count_items(f);
        fclose(f);
        
        size_t cars_mem = sizeof(car_t) * count, keys_mem = sizeof(key_value_t) * count;
        double percent_time = (res_shaker - res_quick) / res_shaker * 100;
        double percent_memory = (double)keys_mem / cars_mem * 100;
        
        printf("| %5lu | %13.5lf | %11.5lf | %19.2lf%% | %12lu | %11lu | %14.2lf |\n", count, res_quick, res_shaker, percent_time, cars_mem, keys_mem, percent_memory);
    }
    printf(ST_SEPARATOR);
    return OK;
}
