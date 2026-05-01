//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_ROTATEDATA_H
#define LAB_03_ROTATEDATA_H
#include "Component/SceneObject/Model/Point/Point.h"

class RotateData
{
public:
    RotateData() noexcept = default;
    RotateData(double angle_x, double angle_y, double angle_z, const Point &center) noexcept;

    double get_angle_x() const noexcept;
    double get_angle_y() const noexcept;
    double get_angle_z() const noexcept;

    double get_center_x() const noexcept;
    double get_center_y() const noexcept;
    double get_center_z() const noexcept;

private:
    double _angle_x, _angle_y, _angle_z;
    Point _center;
};

#endif //LAB_03_ROTATEDATA_H