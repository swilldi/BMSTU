//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "QtDrawer.h"

QtDrawer::QtDrawer(std::shared_ptr<QGraphicsScene> scene) : _scene(scene)
{
    _width = scene->width();
    _height = scene->height();
}

void QtDrawer::draw_line(const Point &a, const Point &b)
{
    _scene->addLine(a.get_x(), a.get_y(), b.get_x(), b.get_y(), { Qt::white });
}

void QtDrawer::draw_line(double x1, double y1, double x2, double y2)
{
    _scene->addLine(x1, y1, x2, y2, { Qt::white });
}

void QtDrawer::clear()
{
    _scene->clear();
}

size_t QtDrawer::get_height() const noexcept
{
    return _height;
}

size_t QtDrawer::get_width() const noexcept
{
    return _width;
}
