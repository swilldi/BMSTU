//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_VECTOR3D_HH
#define LAB_03_VECTOR3D_HH

#include "Vector3D/Vector3D.h"
#include "Concepts/Concepts.h"
#include "Exceptions/Vector/VectorExceptions.h"

// === Конструкторы ===
template <ConvertibleToDouble T>
Vector3D<T>::Vector3D() : _x(0), _y(0), _z(0) {}

template <ConvertibleToDouble T>
Vector3D<T>::Vector3D(T x, T y, T z) : _x(x), _y(y), _z(z) {}

template <ConvertibleToDouble T>
Vector3D<T>::Vector3D(T value) : _x(value), _y(value), _z(value) {}

// === Доступ к значениям вектора ===
template <ConvertibleToDouble T>
T Vector3D<T>::get_x() const noexcept
{
    return _x;
}

template <ConvertibleToDouble T>
T Vector3D<T>::get_y() const noexcept
{
    return _y;
}

template <ConvertibleToDouble T>
T Vector3D<T>::get_z() const noexcept
{
    return _z;
}

template <ConvertibleToDouble T>
void Vector3D<T>::set_x(const T &value) noexcept
{
    _x = value;
}

template <ConvertibleToDouble T>
void Vector3D<T>::set_y(const T &value) noexcept
{
    _y = value;
}

template <ConvertibleToDouble T>
void Vector3D<T>::set_z(const T &value) noexcept
{
    _z = value;
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::operator+(const Vector3D &other) const noexcept
{
    return Vector3D(_x + other._x(), _y + other._y(), _z + other._z());
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::operator-(const Vector3D &other) const noexcept
{
    return Vector3D(_x - other._x(), _y - other._y(), _z - other._z());
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::operator*(const Vector3D &other) const noexcept
{
    return Vector3D(_x * other._x, _y * other._y, _z * other._z);
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::operator*(const T &value) const noexcept
{
    return Vector3D(_x * value, _y * value, _z * value);
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::operator/(const T &value) const noexcept
{
    if (std::abs(value) <= 1e-6)
        throw VectorDivisionByZero();
    return Vector3D(_x / value, _y / value, _z / value);
}

template <ConvertibleToDouble T>
T Vector3D<T>::dot(const Vector3D &other) const noexcept
{
    return _x * other._x + _y * other._y + _z * other._z;
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::cross(const Vector3D &other) const noexcept
{
    return Vector3D(_y * other._z - _z * other._y, _z * other._x - _x * other._z,
                    _x * other._y - _y * other._x);
}

template <ConvertibleToDouble T>
T Vector3D<T>::length() const noexcept
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

template <ConvertibleToDouble T>
Vector3D Vector3D<T>::normalized() const
{
    T len = length();
    if (len == 0)
        return *this;
    return *this / len;
}

template <ConvertibleToDouble T>
bool Vector3D<T>::operator==(const Vector3D &other) const
{
    return _x == other._x && _y == other._y && _z == other._z;
}

template <ConvertibleToDouble T>
Vector3D<T> operator*(T value, const Vector3D<T> &vector)
{
    return vector * value;
}

template <ConvertibleToDouble T>
std::ostream &operator<<(std::ostream &os, const Vector3D<T> vector)
{
    os << "(" << vector.get_x() << ", " << vector.get_y() << ", " << vector.get_z() << ")";
    return os;
}

template <ConvertibleToDouble T>
Vector3D<T> Vector3D<T>::zero()
{
    return Vector3D(0, 0, 0);
}

template <ConvertibleToDouble T>
Vector3D<T> Vector3D<T>::one()
{
    return Vector3D(1, 1, 1);
}
template <ConvertibleToDouble T>
Vector3D<T> Vector3D<T>::up()
{
    return Vector3D(0, 1, 0);
}
template <ConvertibleToDouble T>
Vector3D<T> Vector3D<T>::right()
{
    return Vector3D(1, 0, 0);
}

template <ConvertibleToDouble T>
Vector3D<T> Vector3D<T>::forward()
{
    return Vector3D(0, 0, -1);
}

#endif //LAB_03_VECTOR3D_HH
