//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DEFAULTCOORDINATECONVERT_H
#define LAB_03_DEFAULTCOORDINATECONVERT_H
#include "Strategies/CoordinateConvert/BaseCoordinateConvert.h"

class DefaultCoordinateConver : public BaseCoordinateConvert
{
public:
    DefaultCoordinateConver() = default;
    virtual ~DefaultCoordinateConver() override = default;

    void convert_points(std::vector<Point> &points, size_t width, size_t height) override;
};

#endif //LAB_03_DEFAULTCOORDINATECONVERT_H