#include <cstdio>
#include "edge.h"


void edge_init(edge_t &edge, size_t from_index, size_t to_index)
{
    edge.from_index = from_index;
    edge.to_index = to_index;
}

// чтение ребра из файла
error_code edge_read_from_file(edge_t &edge, FILE* const f)
{
    if (!f)
        return FILE_INVALID;

    error_code rc = OK;

    long from_index, to_index;
    if (fscanf(f, "%ld %ld", &from_index, &to_index) == 2)
    {
        edge_init(edge, from_index, to_index);
    }
    else
    {
        rc = FILE_INVALID_TYPE_DATA;
    }


    return rc;
}

// запись ребра в память
error_code edge_write_to_file(FILE* const f, const edge_t &edge)
{
    if (!f)
        return FILE_INVALID;

    fprintf(f, "%lu %lu\n", edge.from_index, edge.to_index);
    return OK;
}

