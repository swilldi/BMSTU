//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "ListModelImpl.h"


ListModelImpl::ListModelImpl() : _points(std::vector<Point>()), _edges(std::vector<Edge>()) { }

void ListModelImpl::add_point(const Point &point)
{
    _points.push_back(point);
}

void ListModelImpl::add_edge(const Edge &edge)
{
    _edges.push_back(edge);
}

void ListModelImpl::set_center(const Point &center) noexcept
{
    _center = center;
}

std::vector<Point> ListModelImpl::get_points() noexcept
{
    return _points;
}

const std::vector<Point> &ListModelImpl::get_points() const noexcept
{
    return _points;
}

std::vector<Edge> ListModelImpl::get_edges() const noexcept
{
    return _edges;
}

Point ListModelImpl::get_center() noexcept
{
    return _center;
}

const Point &ListModelImpl::get_center() const noexcept
{
    return _center;
}

// TODO
void ListModelImpl::transform(std::shared_ptr<TransformAction> action)
{
    for (auto &point: _points)
        action->transform(point);

    action->transform(_center);
}
