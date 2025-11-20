// #define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "exit_code.h"
#include "io_func.h"
#include "enums.h"
#include "queue_array_func.h"
#include "queue_list_func.h"
#include "test.h"
#include <time.h>


#define PRE_TEST_COUNT 50
#define TEST_COUNT 50

// Подсчёт строк в файле
#define BUFFER_LEN 128
size_t count_lines_in_file(FILE *f)
{
    size_t count = 0;
    char buffer[BUFFER_LEN];
    while (fgets(buffer, sizeof(buffer), f))
        count++;
    rewind(f);
    return count;
}

// Считывание слов в двумерный массив
q_type *read_data_from_file(const char *filename, size_t *count)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        return NULL;
    }

    *count = count_lines_in_file(f);
    if (*count == 0) {
        fclose(f);
        return NULL;
    }

    // Выделяем память под массив строк фиксированной длины
    q_type *arr = malloc(*count * sizeof(q_type));
    if (!arr) {
        fclose(f);
        return NULL;
    }

    for (size_t i = 0; i < *count; i++) {
        if (fscanf(f, "%f", &arr[i]) != 1)
        {
            fclose(f);
            free(arr);
            return NULL;
        }
        
    }

    fclose(f);
    return arr;
}

int test_queue_array(q_type *arr, size_t n, double *res_time)
{
    int rc;
    queue_array_t *queue = create_queue_array();

    // ПРОГРЕВОЧНЫЕ ТЕСТЫ
    for (size_t test_i = 0; test_i < PRE_TEST_COUNT; test_i++)
    {
        q_type tmp;
        for (size_t i = 0; i < n; i++)
        {
            rc = push_array(queue, arr[i]);
            if (rc != OK)
                return rc;
        }

        for (size_t i = 0; i < n; i++)
        {
           rc = pop_array(queue, &tmp);
           if (rc != OK)
                return rc;
        }
    }

    // ОСНОВНЫЕ ТЕСТЫ
    double total_time = 0;
    clock_t start, end;
    for (size_t test_i = 0; test_i < TEST_COUNT; test_i++)
    {
        q_type tmp;

        
        start = clock();
        for (size_t i = 0; i < n; i++)
        {
            rc = push_array(queue, arr[i]);
            if (rc != OK)
                return rc;
        }
        for (size_t i = 0; i < n; i++)
        {
            rc = pop_array(queue, &tmp);
            if (rc != OK)
                return rc;
        }

        end = clock();

        // printf("start: %ld %ld\n", start.tv_sec, start.tv_nsec);
        // printf("end:   %ld %ld\n", end.tv_sec, end.tv_nsec);

        total_time += end - start;
    }
    
    destroy_queue_array(queue);

    *res_time = total_time / TEST_COUNT / CLOCKS_PER_SEC;

    return OK;
}

int test_queue_list(q_type *arr, size_t n, double *res_time)
{
    int rc;
    queue_list_t *queue = create_queue_list();

    // ПРОГРЕВОЧНЫЕ ТЕСТЫ
    for (size_t test_i = 0; test_i < PRE_TEST_COUNT; test_i++)
    {
        q_type tmp;
        for (size_t i = 0; i < n; i++)
        {
            rc = push_list(queue, arr[i]);
            if (rc != OK)
                return rc;
        }

        for (size_t i = 0; i < n; i++)
        {
           rc = pop_list(queue, &tmp);
           if (rc != OK)
                return rc;
        }
    }

    // ОСНОВНЫЕ ТЕСТЫ
    double total_time = 0;
    for (size_t test_i = 0; test_i < TEST_COUNT; test_i++)
    {
        q_type tmp;
        clock_t start, end;

        start = clock();
        for (size_t i = 0; i < n; i++)
        {
            rc = push_list(queue, arr[i]);
            if (rc != OK)
                return rc;
        }

        for (size_t i = 0; i < n; i++)
        {
           rc = pop_list(queue, &tmp);
           if (rc != OK)
                return rc;
        }
        end = clock();

        total_time += end - start; 
    }

    destroy_queue_list(queue);

    *res_time = total_time / TEST_COUNT / CLOCKS_PER_SEC;

    return OK;

}

char *file_paths[] = 
{
    "./files_for_tests/elems_10.txt",
    "./files_for_tests/elems_50.txt",
    "./files_for_tests/elems_100.txt",
    "./files_for_tests/elems_500.txt",
    "./files_for_tests/elems_1000.txt",
    "./files_for_tests/elems_2000.txt",
    "./files_for_tests/elems_2500.txt",
    "./files_for_tests/elems_3000.txt",
    "./files_for_tests/elems_5000.txt",
    "./files_for_tests/elems_6000.txt",
    "./files_for_tests/elems_7000.txt",
    "./files_for_tests/elems_8000.txt",
    "./files_for_tests/elems_9000.txt",
    "./files_for_tests/elems_10000.txt"
};


#define TABLE_SEPARATOR "|--------------------------------------------------------------------------------------------|\n"

int run_compare_tests(void)
{
    int rc;
    size_t file_count = sizeof(file_paths) / sizeof(file_paths[0]);

    printf(
        TABLE_SEPARATOR
        "| Количетсво |              Время, сек               |             Память, байт              |\n"
        "| элементов  |---------------------------------------|---------------------------------------|\n"
        "|            |   массив  |   список  | массив/список |   массив  |   список  | массив/список |\n"
        TABLE_SEPARATOR
    );

    for (size_t i = 0; i < file_count; i++)
    {
        size_t n;
        q_type *arr = read_data_from_file(file_paths[i], &n);

        double time_array = 0, time_list = 0;
        
        long memory_array = sizeof(q_type) * QUEUE_LEN;
        long memory_list = get_size_node_t() * n + get_size_queue_list_t();

        rc = test_queue_array(arr, n, &time_array);
        if (rc != OK)
        {
            free(arr);
            return rc;
        }
        rc = test_queue_list(arr, n, &time_list);
        if (rc != OK)
        {
            free(arr);
            return rc;
        }

        double percent_time = (time_list - time_array) / time_list * 100 ;
        double percent_memory = ((double)memory_array - memory_list) / memory_array * 100;

        printf(
            "| %10lu | %9lf | %9lf | %12.2lf%% | %9lu | %9lu | %12.2lf%% |\n",
            n, time_array, time_list, percent_time, memory_array, memory_list, percent_memory
        );

        free(arr);
    }

    printf(TABLE_SEPARATOR);

    return OK;
}
