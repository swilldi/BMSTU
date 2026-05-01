//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_SCALEDATA_H
#define LAB_03_SCALEDATA_H

#include "Component/SceneObject/Model/Point/Point.h"

class ScaleData
{
public:
    ScaleData() noexcept = default;
    ScaleData(double kx, double ky, double kz, const Point &center) noexcept;

    double get_kx() const noexcept;
    double get_ky() const noexcept;
    double get_kz() const noexcept;

    double get_center_x() const noexcept;
    double get_center_y() const noexcept;
    double get_center_z() const noexcept;

private:
    double _kx, _ky, _kz;
    Point _center;
};

#endif //LAB_03_SCALEDATA_H