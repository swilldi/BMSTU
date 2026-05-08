//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "Edge.h"

Edge::Edge(size_t from, size_t to): _from(from), _to(to) { }

size_t Edge::get_from() const
{
    return _from;
}

size_t Edge::get_to() const
{
    return _to;
}

void Edge::set_from(size_t from)
{
    _from = from;
}

void Edge::set_to(size_t to)
{
    _to = to;
}
