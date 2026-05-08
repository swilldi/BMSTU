//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "ScaleData.h"

ScaleData::ScaleData(double kx, double ky, double kz, const Point &center) noexcept :
    _kx(kx), _ky(ky), _kz(kz), _center(center) { }

double ScaleData::get_kx() const noexcept
{
    return _kx;
}

double ScaleData::get_ky() const noexcept
{
    return _ky;
}

double ScaleData::get_kz() const noexcept
{
    return _kz;
}


double ScaleData::get_center_x() const noexcept
{
    return _center.get_x();
}

double ScaleData::get_center_y() const noexcept
{
    return _center.get_y();
}

double ScaleData::get_center_z() const noexcept
{
    return _center.get_z();
}