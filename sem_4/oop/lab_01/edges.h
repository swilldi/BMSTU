#ifndef EDGES_H
#define EDGES_H

#include "edge.h"

struct edges
{
    edge_t *data;
    size_t count;
};

using edges_t = struct edges;

error_code edges_allocate(edges_t* &edges, size_t count);
void edges_free(edges_t &edges);
void edges_init(edges_t &edges);
error_code edges_check(const edges_t &edges);

error_code count_edges_read_from_file(size_t &count, FILE* const f);
error_code edges_read_from_file(edges_t &edges, FILE* const f);
error_code edges_write_to_file(FILE* const f, const edges_t &edges);



#endif // EDGES_H
