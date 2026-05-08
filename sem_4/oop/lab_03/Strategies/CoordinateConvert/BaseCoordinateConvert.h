//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASECOORDINATECONVERT_H
#define LAB_03_BASECOORDINATECONVERT_H
#include "Component/SceneObject/Model/Point/Point.h"

#include <vector>

class BaseCoordinateConvert
{
public:
    BaseCoordinateConvert() = default;
    virtual ~BaseCoordinateConvert() = default;

    virtual void convert_points(std::vector<Point> &points, size_t width, size_t height) = 0;
};

#endif //LAB_03_BASECOORDINATECONVERT_H