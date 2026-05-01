//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "MoveData.h"

MoveData::MoveData(const Point &point) noexcept : _dx(point.get_x()), _dy(point.get_y()), _dz(point.get_z()) { }

MoveData::MoveData(double dx, double dy, double dz) noexcept : _dx(dx), _dy(dy), _dz(dz) { }

double MoveData::get_dx() const noexcept
{
    return _dx;
}

double MoveData::get_dy() const noexcept
{
    return _dy;
}

double MoveData::get_dz() const noexcept
{
    return _dz;
}
