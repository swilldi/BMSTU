//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "DefaultCoordinateConvert.h"

void DefaultCoordinateConver::convert_points(std::vector<Point> &points, size_t width, size_t height)
{
    size_t cx = static_cast<size_t>(width / 2.0);
    size_t cy = static_cast<size_t>(height / 2.0);

    for (auto &point : points)
    {
        point.set_x(point.get_x() * cx + cx);
        point.set_y(-point.get_y() * cy + cy);
    }
}
