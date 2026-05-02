//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_VECTOR3D_H
#define LAB_03_VECTOR3D_H

#include <iostream>
#include "Concepts/Concepts.h"

template <ConvertibleToDouble T>
class Vector3D
{
public:
    // === Конструкторы ===
    Vector3D();
    Vector3D(T x, T y, T z);
    explicit Vector3D(T value);

    // === Деструктор ===
    ~Vector3D() = default;

    // === Доступ к значениям вектора ===
    T get_x() const noexcept;
    T get_y() const noexcept;
    T get_z() const noexcept;

    void set_x(const T &value) noexcept;
    void set_y(const T &value) noexcept;
    void set_z(const T &value) noexcept;

    Vector3D operator+(const Vector3D &other) const;
    Vector3D operator-(const Vector3D &other) const;
    Vector3D operator*(const Vector3D &other) const;

    Vector3D operator*(const T &value) const noexcept;
    Vector3D operator/(const T &value) const noexcept;

    T dot(const Vector3D &other) const noexcept;
    Vector3D cross(const Vector3D &other) const noexcept;
    T length() const noexcept;
    Vector3D normalized() const;

    bool operator==(const Vector3D &other) const;

    static Vector3D zero();
    static Vector3D one();
    static Vector3D up();
    static Vector3D right();
    static Vector3D forward();

private:
    T _x, _y, _z;
};

template <ConvertibleToDouble T>
Vector3D<T> operator*(T value, const Vector3D<T> &vector);

template <ConvertibleToDouble T>
std::ostream &operator<<(std::ostream &os, const Vector3D<T> vector);

#include "Vector3D.hpp"

#endif //LAB_03_VECTOR3D_H