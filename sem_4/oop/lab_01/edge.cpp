#include <cstdio>
#include "edge.h"

// Инициализация ребра
void edge_init(edge_t &edge, size_t from_index, size_t to_index)
{
    edge.from_index = from_index;
    edge.to_index = to_index;
}

// Чтение ребра из файла
error_code edge_read_from_file(edge_t &edge, FILE* const f)
{
    error_code rc = OK;
    if (!f)
        return FILE_INVALID;

    long from_index, to_index;
    if (fscanf(f, "%ld %ld", &from_index, &to_index) != 2)
    {
        rc = FILE_INVALID_TYPE_DATA;
    }
    else if (from_index < 0 || to_index < 0)
    {
        rc = EDGES_INVALID_INDEX_RANGE;
    }
    else
    {
        edge_init(edge, from_index, to_index);
    }

    return rc;
}

// Запись ребра в файл
error_code edge_write_to_file(FILE* const f, const edge_t &edge)
{
    if (!f)
        return FILE_INVALID;

    fprintf(f, "%lu %lu\n", edge.from_index, edge.to_index);
    return OK;
}

