//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#include "BaseModelBuilder.h"

BaseModelBuilder::BaseModelBuilder(std::shared_ptr<ModelReader> reader) : _reader(reader) { }

bool BaseModelBuilder::build_points()
{
    if (_part != POINTS)
        return false;

    if (!_impl)
        _impl = create_impl();

    auto points = _reader->read_points();
    for (const auto &point : *points)
        _impl->add_point(point);

    ++_part;
    return true;
}

bool BaseModelBuilder::build_edges()
{
    if (_part != EDGES)
        return false;

    auto edges = _reader->read_edges();
    for (const auto &edge : *edges)
        _impl->add_edge(edge);

    ++_part;
    return true;
}

bool BaseModelBuilder::build_center()
{
    if (_part != CENTER)
        return false;

    const auto &points = _impl->get_points();
    double x_min = points[0].get_x(), x_max = points[0].get_x(),
           y_min = points[0].get_y(), y_max = points[0].get_y(),
           z_min = points[0].get_z(), z_max = points[0].get_z();

    for (const auto &point : points)
    {
        x_min = std::min(x_min, point.get_x());
        x_max = std::max(x_max, point.get_x());

        y_min = std::min(y_min, point.get_y());
        y_max = std::max(y_max, point.get_y());

        z_min = std::min(z_min, point.get_z());
        z_max = std::max(z_max, point.get_z());
    }

    double cx = (x_min + x_max) / 2,
           cy = (y_min + y_max) / 2,
           cz = (z_min + z_max) / 2;

    _impl->set_center({ cx, cy, cz });

    _part = POINTS;
    return true;
}

std::shared_ptr<BaseModelImpl> BaseModelBuilder::create_product()
{
    return _impl;
}
