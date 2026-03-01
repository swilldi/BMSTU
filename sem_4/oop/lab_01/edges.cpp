#include <cstdlib>
#include <cstdio>

#include "edges.h"

// Выделение памяти для массива ребер
error_code edges_allocate(edge_t* &edges, size_t count)
{
    error_code rc = OK;
    edge_t *tmp_arr = (edge_t*)malloc(sizeof(edge_t) * count);
    if (!tmp_arr)
        return MEMORY_ERR;

    edges = tmp_arr;

    return rc;
}

// Инициализация структуры с массивом ребер
void edges_init(edges_t &edges)
{
    edges.data = NULL;
    edges.count = 0;
}

// Освобождение памяти из под массива ребер
void edges_free(edges_t &edges)
{
    if (edges.data)
        free(edges.data);

    edges_init(edges);
}

error_code edges_check(const edges_t &edges)
{
    error_code rc = OK;
    if (!edges.data)
        rc = POINTS_INVALID;
    else if (edges.count <= 0)
        rc = POINTS_EMPTY;
    
    return rc;
}

// чтение количества ребер в файле
error_code count_edges_read_from_file(size_t &count, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;

    long tmp_count;
    if (fscanf(f, "%ld", &tmp_count) != 1)
        rc = FILE_INVALID_TYPE_DATA;
    else if (tmp_count <= 0)
        rc = FILE_DATA_INVALID_RANGE;
    else
        count = tmp_count;

    return rc;
}

// чтение индексов точек из файла
error_code edges_data_read_from_file(edges_t &edges, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;
    if (edges.count <= 0)
        return EDGES_EMPTY;

    // чтение ребер
    rc = edges_allocate(edges.data, edges.count);
    for (size_t i = 0; rc == OK && i < edges.count; i++)
    {
        rc = edge_read_from_file(edges.data[i], f);
        if (rc != OK)
            edges_free(edges);
    }

    return rc;
}

// чтение ребер из файла
error_code edges_read_from_file(edges_t &edges, FILE* const f)
{
    if (!f)
        return FILE_INVALID;

    // чтение количества ребер и выделение памяти
    error_code rc = count_edges_read_from_file(edges.count, f);
    if (rc == OK)
    {
        rc = edges_data_read_from_file(edges, f);
    }

    return rc;
}

// запись ребер в файл
error_code edges_write_to_file(FILE* const f, const edges_t &edges)
{
    error_code rc = edges_check(edges);
    if (rc != OK)
        return rc;
    if (!f)
        return FILE_INVALID;

    fprintf(f, "%ld\n", edges.count);
    for (size_t i = 0; rc == OK && i < edges.count; i++)
    {
        edge_t edge = edges.data[i];
        rc = edge_write_to_file(f, edge);
    }

    return rc;
}











