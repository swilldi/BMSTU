#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "graph_matr.h"
#include "graph_list.h"

#define PRE_TEST_COUNT 5
#define TEST_COUNT 10


// Функция для измерения времени выполнения (в секундах)
double get_time_sec(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Тестирование матричной реализации
void test_matrix(graph_matr_t *g1, int n, int m, double *time, long *mem)
{
    srand(42);
    for (int e = 0; e < m; ++e)
    {
        int from = rand() % n;
        int to = rand() % n;
        if (from == to) { --e; continue; } // без петель
        int w = 1 + rand() % 100;
        graph_add_edge(g1, from, to, w);
    }
    *mem = graph_memory_capacity(g1);
    double t1 = get_time_sec();
    matrix_t dist1 = graph_shortest_paths(g1);
    double t2 = get_time_sec();
    matrix_destoy(dist1, n);
    *time = t2 - t1;
}

// Тестирование списочной реализации
void test_list(graph_list_t *g2, int n, int m, double *time, long *mem)
{
    srand(42);
    for (int e = 0; e < m; ++e)
    {
        int from = rand() % n;
        int to = rand() % n;
        if (from == to) { --e; continue; }
        int w = 1 + rand() % 100;
        graph_list_add_edge(g2, from, to, w);
    }
    *mem = graph_list_memory_capacity(g2);
    double t3 = get_time_sec();
    matrix_t dist2 = graph_list_shortest_paths(g2);
    double t4 = get_time_sec();
    matrix_destoy(dist2, n);
    *time = t4 - t3;
}



void run_test(void)
{
    int ns[] = {5, 10, 50, 100, 300, 500, 700, 1000};
    double percents[] = {0.1, 0.2, 0.5, 0.7, 1.0};
    int n_count = sizeof(ns) / sizeof(ns[0]);
    int p_count = sizeof(percents) / sizeof(percents[0]);

    printf(
        "---------------------------------------------------------------------------------\n"
        "|  Кол-во   |   Кол-во  |  Матричное представление  |   Списочное представление |\n"
        "|  вершин   |   ребер   |--------------------------------------------------------\n"
        "|           |           | Память, байт | Время, сек | Память, байт | Время, сек |\n"
        "---------------------------------------------------------------------------------\n"
    );
    for (int i = 0; i < n_count; ++i)
    {
        int n = ns[i];
        int max_m = n * (n - 1); // для ориентированного графа без петель
        for (int j = 0; j < p_count; ++j)
        {
            int m = (int)(max_m * percents[j]);
            
            // == Тест матрицы ==
            // память
            graph_matr_t *g1 = graph_create(n);
            long mem1;
            graph_destroy(g1);
            // время выполнения
            double time1 = 0;
            for (size_t i = 0; i < PRE_TEST_COUNT + TEST_COUNT; i++)
            {
                double res;
                g1 = graph_create(n);
                test_matrix(g1, n, m, &res, &mem1);
                if (i >= PRE_TEST_COUNT)
                    time1 += res;
                graph_destroy(g1);
            }
            time1 /= TEST_COUNT;
            

            // == Тест списка ==
            // память
            graph_list_t *g2 = graph_list_create(n);
            long mem2;
            graph_list_destroy(g2);
            // время выполенения
            double time2 = 0;
            for (size_t i = 0; i < PRE_TEST_COUNT + TEST_COUNT; i++)
            {
                double res;
                g2 = graph_list_create(n);            
                test_list(g2, n, m, &res, &mem2);
                if (i >= PRE_TEST_COUNT)
                    time2 += res;
                graph_list_destroy(g2);
            }
            time2 /= TEST_COUNT;
            

            printf("| %9d | %9d | %12ld | %10.5f | %12ld | %10.5f |\n", n, m, mem1, time1, mem2, time2);
        }
        printf("---------------------------------------------------------------------------------\n");
    }
}
