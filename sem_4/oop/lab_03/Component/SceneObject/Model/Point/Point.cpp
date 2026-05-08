//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "Point.h"
#include "Matrix/Matrix.h"

#include <complex>

#define EPS 1e-9

Point::Point(double x, double y, double z) noexcept: _x(x), _y(y), _z(z), _w(0) {}

// === Геттеры ===
double Point::get_x() const noexcept
{
    return _x;
}

double Point::get_y() const noexcept
{
    return _y;
}

double Point::get_z() const noexcept
{
    return _z;
}

double Point::get_w() const noexcept
{
    return _w;
}

// ===  Сеттеры ===
void Point::set_x(double x) noexcept
{
    _x = x;
}

void Point::set_y(double y) noexcept
{
    _y = y;
}

void Point::set_z(double z) noexcept
{
    _z = z;
}

void Point::set_w(double w) noexcept
{
    _w = w;
}

// === ??? ===
double Point::distance_to(const Point &other) const noexcept
{
    return std::sqrt(std::pow(_x - other._x, 2) + std::pow(_y - other._y, 2) + std::pow(_z - other._z, 2));
}

void Point::transform(const Matrix<double> &matrix)
{
    Matrix<double> current{ { _x }, { _y }, { _z }, { 1.0 } };
    Matrix<double> new_position = matrix * current;

    _x = new_position[0][0];
    _y = new_position[1][0];
    _z = new_position[2][0];
    _w = new_position[3][0];
}

// === Операторы ===
bool Point::equal(const Point &other) const noexcept
{
    return std::abs(_x - other._x) <= EPS && std::abs(_y - other._y) <= EPS && std::abs(_z - other._z) <= EPS;
}

bool Point::operator==(const Point &other) const noexcept
{
    return equal(other);
}

bool Point::not_equal(const Point &other) const noexcept
{
    return !equal(other);
}

Point &Point::add(const Point &other) noexcept
{
    _x += other._x;
    _y += other._y;
    _z += other._z;

    return *this;
}

Point &Point::operator+=(const Point &other) noexcept
{
    add(other);
    return *this;
}

Point Point::sum(const Point &other) const noexcept
{
    Point tmp(*this);
    tmp += other;
    return tmp;
}

Point Point::operator+(const Point &other) const noexcept
{
    return sum(other);
}

Point &Point::subtract(const Point &other) noexcept
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;

    return *this;
}
Point &Point::operator-=(const Point &other) noexcept
{
    subtract(other);
    return *this;
}

Point Point::diff(const Point &other) const noexcept
{
    Point tmp(*this);
    tmp.subtract(other);
    return tmp;
}
Point Point::operator-(const Point &other) const noexcept
{
    return diff(other);
}

std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "(" << point.get_x() << ", " << point.get_y() << ", " << point.get_z() << ")";
    return os;
}
