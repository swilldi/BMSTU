//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_POINT_H
#define LAB_03_POINT_H

#include "Concepts/Concepts.h"

template<ConvertibleToDouble T>
class Matrix;

class Point
{
public:
    Point() noexcept = default;
    Point(double x, double y, double z) noexcept;

    Point(const Point &other) = default;
    Point &operator=(const Point &other) = default;
    Point(Point &&other) = default;
    Point &operator=(Point &&other) = default;

    ~Point() = default;

    double get_x() const noexcept;
    double get_y() const noexcept;
    double get_z() const noexcept;
    double get_w() const noexcept;

    void set_x(double x) noexcept;
    void set_y(double y) noexcept;
    void set_z(double z) noexcept;
    void set_w(double w) noexcept;

    double distance_to(const Point& other) const noexcept;
    void transform(const Matrix<double> &matrix);

    bool equal(const Point &other) const noexcept;
    bool operator==(const Point &other) const noexcept;
    bool not_equal(const Point &other) const noexcept;

    Point &add(const Point &other) noexcept;
    Point &operator+=(const Point &other) noexcept;

    Point sum(const Point &other) const noexcept;
    Point operator+(const Point &other) const noexcept;

    Point &subtract(const Point &other) noexcept;
    Point &operator-=(const Point &other) noexcept;

    Point diff(const Point &other) const noexcept;
    Point operator-(const Point &other) const noexcept;

private:
    double _x, _y, _z, _w;
};

#include <iostream>

std::ostream &operator<<(const std::ostream &os, const Point &point);

#endif //LAB_03_POINT_H