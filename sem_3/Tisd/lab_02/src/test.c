#include "test.h"

int test(FILE *f, sort_type sort_method, double *res)
{
    clock_t start, end;
    *res = 0;
    car_t *table = NULL;
    size_t len;
    int rc;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        sort_method(table, len, sizeof(car_t), cmp_car_prise);
    }
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        
        start = clock();
        sort_method(table, len, sizeof(car_t), cmp_car_prise);
        end = clock();

        *res = (double)(end - start + *res) / 2;
    }

    *res /= CLOCKS_PER_SEC;

    free(table);
    table = NULL;
    return rc;
}

int test_by_key(FILE *f, sort_type sort_method, double *res)
{
    clock_t start, end;
    *res = 0;
    car_t *table = NULL;
    key_value_t *table_key = NULL;
    size_t len;
    int rc;

    for (size_t i = 0; i < PRE_TEST_COUNT; i++)
    {
        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        rc = get_table_key(table, &table_key, len);
        if (rc != OK)
            break;
        sort_method(table_key, len, sizeof(car_t), cmp_car_prise_by_key);
    }
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        rc = read_cars(f, &table, &len);
        if (rc != OK)
            break;
        
        start = clock();
        rc = get_table_key(table, &table_key, len);
        if (rc != OK)
            break;
        sort_method(table_key, len, sizeof(car_t), cmp_car_prise_by_key);
        end = clock();

        *res = (double)(end - start + *res) / 2;
    }

    *res /= CLOCKS_PER_SEC;

    free(table);
    table = NULL;
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
    FILE *f = NULL;
    double res_table, res_key;
    int rc;
    char *(paths[80]) = {
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_20.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_100.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_500.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_1000.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_2000.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_5000.txt"
        // "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_10000.txt"
    };

    printf(
        "--------+---------------+-------------+-----------------------\n"
        "| count | by_table, сек | by_key, сек | by_key / by_table, %% |\n"
        "--------+---------------+-------------+-----------------------\n"
    );

    for (size_t i = 0; i < 7; i++)
    {
        rc = open_file(&f, (char *)paths[i]);
        if (rc != OK)
            return rc;

        rc = test(f, sort, &res_table);
        if (rc != OK)
            return rc;
        rc = test_by_key(f, sort, &res_key);
        if (rc != OK)
            return rc;

        double percent = (res_table - res_key) / res_table * 100;
        
        printf("| %5d | %13.5lf | %11.5lf | %19.2lf%% |\n", get_count(i), res_table, res_key, percent);
    }
    printf("--------+---------------+-------------+-----------------------\n");
    return OK;
}

int test_sort(test_type test_f)
{
    FILE *f = NULL;
    double res_shaker, res_bumble;
    int rc;
    char *(paths[80]) = {
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_20.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_100.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_500.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_1000.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_2000.txt",
        "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_5000.txt"
        // "/Users/dmitriy/BMSTU/sem_3/Tisd/lab_02/test_files/cars_dataset_10000.txt"
    };

    printf(
        "--------+---------------+-------------+-----------------------\n"
        "| count |  shaker, сек  | bumble, сек |  shaker / bumble, %%  |\n"
        "--------+---------------+-------------+-----------------------\n"
    );

    for (size_t i = 0; i < 7; i++)
    {
        rc = open_file(&f, (char *)paths[i]);
        if (rc != OK)
            return rc;

        rc = test_f(f, shaker_sort, &res_shaker);
        if (rc != OK)
            return rc;
        rc = test_f(f, bumble_sort, &res_bumble);
        if (rc != OK)
            return rc;

        double percent = (res_bumble - res_shaker) / res_bumble * 100;
        
        printf("| %5d | %13.5lf | %11.5lf | %19.2lf%% |\n", get_count(i), res_shaker, res_bumble, percent);
    }
    printf("--------+---------------+-------------+-----------------------\n");
    return OK;
}
