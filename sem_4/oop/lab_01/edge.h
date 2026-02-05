#ifndef EDGE_H
#define EDGE_H

#include <cstdio>
#include "error_codes.h"

struct edge
{
    size_t from_index;
    size_t to_index;
};

using edge_t = struct edge;

void edge_init(edge_t &edge, size_t from_index, size_t to_index);

error_code edge_read_from_file(FILE *f, edge_t &edge);
error_code edge_write_to_file(FILE *f, const edge_t &edge);

#endif // EDGE_H
