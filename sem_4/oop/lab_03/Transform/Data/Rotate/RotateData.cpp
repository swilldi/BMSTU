//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "RotateData.h"

RotateData::RotateData(double angle_x, double angle_y, double angle_z, const Point &center) noexcept :
    _angle_x(angle_x), _angle_y(angle_y), _angle_z(angle_z), _center(center) { }

double RotateData::get_angle_x() const noexcept
{
    return _angle_x;
}

double RotateData::get_angle_y() const noexcept
{
    return _angle_y;
}

double RotateData::get_angle_z() const noexcept
{
    return _angle_z;
}


double RotateData::get_center_x() const noexcept
{
    return _center.get_x();
}

double RotateData::get_center_y() const noexcept
{
    return _center.get_y();
}

double RotateData::get_center_z() const noexcept
{
    return _center.get_z();
}
