//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_EDGE_H
#define LAB_03_EDGE_H

#include <cstddef>

class Edge
{
public:
    Edge() = default;
    Edge(size_t from, size_t to);

    Edge(const Edge &other) = default;
    Edge &operator=(const Edge &other) = default;
    Edge(Edge &&other) = default;
    Edge &operator=(Edge &&other) = default;

    size_t get_from() const;
    size_t get_to() const;

    void set_from(size_t from);
    void set_to(size_t to);

private:
    size_t _from, _to;
};

#endif //LAB_03_EDGE_H