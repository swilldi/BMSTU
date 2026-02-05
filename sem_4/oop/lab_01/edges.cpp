#include <cstdlib>
#include <cstdio>
#include "edges.h"


error_code edges_create(edges_t &edges, size_t count)
{
    edges.data = (edge_t*)malloc(sizeof(edge_t) * count);
    if (!edges.data)
        return MEMORY_ERR;

    edges.count = count;
    return OK;
}

void edges_init(edges_t &edges)
{
    edges.data = NULL;
    edges.count = 0;
}

void edges_free(edges_t &edges)
{
    if (edges.data)
        free(edges.data);
}

error_code count_edges_read_from_file(FILE *f, size_t &count)
{
    if (!f)
        return INVALID_FILE_ERR;

    long tmp_count;
    if (fscanf(f, "%ld", &tmp_count) != 1)
        return INVALID_FILE_DATA;

    if (tmp_count <= 0)
        return INVALID_DATA_RANGE;

    count = tmp_count;
    return OK;
}

error_code edges_read_from_file(FILE *f, edges_t &edges)
{
    if (!f)
        return INVALID_FILE_ERR;

    // чтение количества ребер и выделение памяти
    size_t edges_count;
    error_code rc = count_edges_read_from_file(f, edges_count);
    if (rc != OK)
        return rc;

    rc = edges_create(edges, edges_count);
    if (rc != OK)
        return rc;

    // чтение ребер
    for (size_t i = 0; i < edges.count; i++)
    {
        rc = edge_read_from_file(f, edges.data[i]);
        if (rc != OK)
        {
            edges_free(edges);
            return rc;
        }
    }

    return OK;
}

error_code edges_write_to_file(FILE *f, const edges_t &edges)
{
    if (!f)
        return INVALID_FILE_ERR;

    fprintf(f, "%ld\n", edges.count);
    for (size_t i = 0; i < edges.count; i++)
    {
        edge_t edge = edges.data[i];
        fprintf(f, "%ld %ld\n", edge.from_index, edge.to_index);
    }

    return OK;
}











