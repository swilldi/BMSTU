//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEDRAWER_H
#define LAB_03_BASEDRAWER_H
#include "Component/SceneObject/Model/Point/Point.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void draw_line(const Point &a, const Point &b) = 0;
    virtual void draw_line(double x1, double y1, double x2, double y2) = 0;

    virtual void clear() = 0;

    virtual size_t get_width() const noexcept = 0;
    virtual size_t get_height() const noexcept = 0;

protected:
    size_t _width;
    size_t _height;
};

#endif //LAB_03_BASEDRAWER_H