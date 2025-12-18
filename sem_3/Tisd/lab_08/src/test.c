#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "graph_matr.h"
#include "graph_list.h"

#define TEST_ITERATIONS 10

// Функция для измерения времени выполнения (в секундах)
double get_time_sec()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Функция для измерения используемой памяти (в КБ)
long get_memory_kb()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

// Тестирование матричной реализации
double test_matrix(int n, int m)
{
    graph_matr_t *g = graph_create(n);
    srand(42);
    for (int i = 0; i < m; ++i)
    {
        int from = rand() % n;
        int to = rand() % n;
        int w = 1 + rand() % 100;
        graph_add_edge(g, from, to, w);
    }
    double t1 = get_time_sec();
    matrix_t dist = graph_shortest_paths(g);
    double t2 = get_time_sec();
    long mem = get_memory_kb();
    matrix_destoy(dist, n);
    matrix_destoy(g->vertices, n);
    free(g);
    printf("Matrix: time = %.6f s, mem = %ld KB\n", t2-t1, mem);
    return t2-t1;
}

// Тестирование списочной реализации
double test_list(int n, int m)
{
    graph_list_t *g = graph_list_create(n);
    srand(42);
    for (int i = 0; i < m; ++i)
    {
        int from = rand() % n;
        int to = rand() % n;
        int w = 1 + rand() % 100;
        graph_list_add_edge(g, from, to, w);
    }
    // Здесь должен быть аналог shortest_paths для списков (реализуйте при необходимости)
    double t1 = get_time_sec();
    // TODO: реализовать graph_list_shortest_paths(g)
    double t2 = get_time_sec();
    long mem = get_memory_kb();
    graph_list_destroy(g);
    printf("List:   time = %.6f s, mem = %ld KB\n", t2-t1, mem);
    return t2-t1;
}

int run_test(void)
{
    int n = 500; // число вершин
    int m = 5000; // число рёбер
    printf("Сравнение графов: n = %d, m = %d\n", n, m);
    test_matrix(n, m);
    test_list(n, m);
    return 0;
}
