//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_MOVEDATA_H
#define LAB_03_MOVEDATA_H
#include "Component/SceneObject/Model/Point/Point.h"

class MoveData
{
public:
    MoveData() noexcept = default;
    MoveData(double dx, double dy, double dz) noexcept;
    MoveData(const Point &point) noexcept;

    double get_dx() const noexcept;
    double get_dy() const noexcept;
    double get_dz() const noexcept;

private:
    double _dx, _dy, _dz;
};

#endif //LAB_03_MOVEDATA_H