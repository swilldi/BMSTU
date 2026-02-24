#include <cstdlib>
#include <cstdio>
#include "edges.h"


error_code edges_create(edges_t &edges, size_t count)
{
    error_code rc = OK;

    edges.data = (edge_t*)malloc(sizeof(edge_t) * count);
    if (edges.data)
    {
        edges.count = count;
    }
    else
    {
        rc = MEMORY_ERR;
    }

    return rc;
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

    edges.data = NULL;
    edges.count = 0;
}

error_code edges_is_valid(edges_t edges)
{
    if (!edges.data)
        return EDGES_INVALID;
    if (edges.count <= 0)
        return EDGES_EMPTY;

    return OK;
}

error_code count_edges_read_from_file(FILE* const f, size_t &count)
{
    if (!f)
        return FILE_INVALID;

    error_code rc = OK;
    long tmp_count;
    if (fscanf(f, "%ld", &tmp_count) == 1)
    {
        if (tmp_count <= 0)
            rc = FILE_DATA_INVALID_RANGE;;
    }
    else
    {
        rc = FILE_INVALID_TYPE_DATA;
    }


    count = tmp_count;
    return rc;
}

error_code edges_data_read_from_file(FILE* const f, edges_t &edges)
{
    if (!f)
        return FILE_INVALID;
    if (edges.count <= 0)
        return EDGES_EMPTY;

    // чтение ребер
    error_code rc = OK;
    for (size_t i = 0; i < edges.count; i++)
    {
        rc = edge_read_from_file(f, edges.data[i]);
        if (rc != OK)
        {
            edges_free(edges);
            break;
        }
    }

    return rc;
}

error_code edges_read_from_file(FILE* const f, edges_t &edges)
{
    if (!f)
        return FILE_INVALID;

    // чтение количества ребер и выделение памяти
    size_t edges_count;
    error_code rc = count_edges_read_from_file(f, edges_count);
    if (rc == OK)
    {
        rc = edges_create(edges, edges_count);
        if (rc == OK)
        {
            rc = edges_data_read_from_file(f, edges);
            if (rc != OK)
                edges_free(edges);
        }
    }

    return rc;
}

error_code edges_write_to_file(FILE* const f, const edges_t &edges)
{
    if (!f)
        return FILE_INVALID;
    if (!edges.data)
        return EDGES_INVALID;
    if (edges.count <= 0)
        return EDGES_EMPTY;

    fprintf(f, "%ld\n", edges.count);
    for (size_t i = 0; i < edges.count; i++)
    {
        edge_t edge = edges.data[i];
        fprintf(f, "%ld %ld\n", edge.from_index, edge.to_index);
    }

    return OK;
}











