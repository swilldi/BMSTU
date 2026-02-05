#include "edge.h"
#include <cstdio>

void edge_init(edge_t &edge, size_t from_index, size_t to_index)
{
    edge.from_index = from_index;
    edge.to_index = to_index;
}

error_code edge_read_from_file(FILE *f, edge_t &edge)
{
    if (!f)
        return INVALID_FILE_ERR;

    long from_index, to_index;
    if (fscanf(f, "%ld %ld", &from_index, &to_index) != 2)
        return INVALID_FILE_DATA;

    edge_init(edge, from_index, to_index);

    return OK;
}

error_code edge_write_to_file(FILE *f, const edge_t &edge)
{
    if (!f)
        return INVALID_FILE_ERR;

    fprintf(f, "%lu %lu\n", edge.from_index, edge.to_index);

    return OK;
}

