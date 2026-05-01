//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "MatrixStructure.h"

MatrixStructure::MatrixStructure() : _point_count(0) { }

void MatrixStructure::add_point(const Point &point)
{
    _points.push_back(point);

    resize_matrix(_points.size());
    _point_count = _points.size();
}

void MatrixStructure::add_edge(const Edge &edge)
{
    size_t id_from = edge.get_from();
    size_t id_to = edge.get_to();

    if (id_from >= _point_count || id_to >= _point_count)
        throw nullptr;

    _adjacency_matrix[id_from][id_to] = true;
    _adjacency_matrix[id_to][id_from] = true;
}

void MatrixStructure::set_center(const Point &center) noexcept
{
    _center = center;
}

std::vector<Point> MatrixStructure::get_points() noexcept
{
    return _points;
}

const std::vector<Point> &MatrixStructure::get_points() const noexcept
{
    return _points;
}

std::vector<Edge> MatrixStructure::get_edges() const noexcept
{
    std::vector<Edge> edges;

    for (size_t i = 0; i < _point_count; ++i)
        for (size_t j = i + 1; j < _point_count; ++j)
            if (_adjacency_matrix[i][j])
                edges.emplace_back(i, j);

    return edges;
}

const Point &MatrixStructure::get_center() const noexcept
{
    return _center;
}

Point MatrixStructure::get_center() noexcept
{
    return _center;
}

void MatrixStructure::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &point : _points)
        action->transform(point);

    action->transform(_center);
}

void MatrixStructure::resize_matrix(size_t size)
{
    for (auto &row : _adjacency_matrix)
        row.resize(size, false);

    while (_adjacency_matrix.size() < size)
        _adjacency_matrix.emplace_back(size, false);
}
