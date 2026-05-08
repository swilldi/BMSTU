//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "MatrixModelImpl.h"

#include "Exceptions/Model/ModelException.h"

MatrixModelImpl::MatrixModelImpl() : _point_count(0) { }

void MatrixModelImpl::add_point(const Point &point)
{
    _points.push_back(point);

    resize_matrix(_points.size());
    _point_count = _points.size();
}

void MatrixModelImpl::add_edge(const Edge &edge)
{
    size_t id_from = edge.get_from();
    size_t id_to = edge.get_to();

    if (id_from >= _point_count || id_to >= _point_count)
        // TODO
        throw ModelInvalidEdgeIDException();

    _adjacency_matrix[id_from][id_to] = true;
    _adjacency_matrix[id_to][id_from] = true;
}

void MatrixModelImpl::set_center(const Point &center) noexcept
{
    _center = center;
}

std::vector<Point> MatrixModelImpl::get_points() noexcept
{
    return _points;
}

const std::vector<Point> &MatrixModelImpl::get_points() const noexcept
{
    return _points;
}

std::vector<Edge> MatrixModelImpl::get_edges() const noexcept
{
    std::vector<Edge> edges;

    for (size_t i = 0; i < _point_count; ++i)
        for (size_t j = i + 1; j < _point_count; ++j)
            if (_adjacency_matrix[i][j])
                edges.emplace_back(i, j);

    return edges;
}

const Point &MatrixModelImpl::get_center() const noexcept
{
    return _center;
}

Point MatrixModelImpl::get_center() noexcept
{
    return _center;
}

void MatrixModelImpl::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &point : _points)
        action->transform(point);

    action->transform(_center);
}

void MatrixModelImpl::resize_matrix(size_t size)
{
    for (auto &row : _adjacency_matrix)
        row.resize(size, false);

    while (_adjacency_matrix.size() < size)
        _adjacency_matrix.emplace_back(size, false);
}
