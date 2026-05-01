//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "ListStructure.h"


ListStructure::ListStructure() : _points(std::vector<Point>()), _edges(std::vector<Edge>()) { }

void ListStructure::add_point(const Point &point)
{
    _points.push_back(point);
}

void ListStructure::add_edge(const Edge &edge)
{
    _edges.push_back(edge);
}

void ListStructure::set_center(const Point &center) noexcept
{
    _center = center;
}

std::vector<Point> ListStructure::get_points() noexcept
{
    return _points;
}

const std::vector<Point> &ListStructure::get_points() const noexcept
{
    return _points;
}

std::vector<Edge> ListStructure::get_edges() const noexcept
{
    return _edges;
}

Point ListStructure::get_center() noexcept
{
    return _center;
}

const Point &ListStructure::get_center() const noexcept
{
    return _center;
}

// TODO
void ListStructure::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &point: _points)
        action->transform(point);

    action->transform(_center);
}
