//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "TxtModelReaderImpl.h"

#include "Exceptions/Model/ModelException.h"

TxtModelReaderImpl::TxtModelReaderImpl(const std::string &filename) : BaseModelReaderImpl(filename) { }

std::shared_ptr<std::vector<Point> > TxtModelReaderImpl::read_points()
{
    _file.clear();
    _file.seekg(0, std::ios::beg);

    size_t point_count;
    if (!(_file >> point_count))
        throw ModelInvalidPointCountException();

    if (point_count <= 0)
        throw ModelInvalidPointCountException();

    std::vector<Point> points(point_count);
    double x, y, z;
    for (size_t i = 0; i < point_count; ++i)
    {
        if (!(_file >> x >> y >> z))
            throw ModelInvalidPointException();

        points[i] = Point(x, y, z);
    }

    return std::make_shared<std::vector<Point>>(points);
}

std::shared_ptr<std::vector<Edge> > TxtModelReaderImpl::read_edges()
{
    _file.clear();
    _file.seekg(0, std::ios::beg);

    size_t point_count;
    if (!(_file >> point_count))
        throw ModelInvalidPointCountException();

    if (point_count <= 0)
        throw ModelInvalidPointCountException();

    double x, y, z;
    for (size_t i = 0; i < point_count; ++i)
        if (!(_file >> x >> y >> z))
            throw ModelInvalidPointException();

    size_t edge_count;
    if (!(_file >> edge_count))
        throw ModelInvalidEdgeCountException();

    if (edge_count <= 0)
        throw ModelInvalidEdgeCountException();

    std::vector<Edge> edges(edge_count);
    size_t id_1, id_2;
    for (size_t i = 0; i < edge_count; ++i)
    {
        if (!(_file >> id_1 >> id_2))
            throw ModelInvalidEdgeException();

        edges[i] = Edge(id_1, id_2);
    }

    return std::make_shared<std::vector<Edge>>(edges);
}
