//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_MATRIXROW_HPP
#define LAB_03_MATRIXROW_HPP

#include "Exceptions/Matrix/MatrixExceptions.h"
#include "Matrix.h"

template <ConvertibleToDouble T>
T &Matrix<T>::MatrixRow::operator[](size_t index)
{
    if (index >= _size)
        throw MatrixOutOfRange();

    return _row[index];
}

template <ConvertibleToDouble T>
const T &Matrix<T>::MatrixRow::operator[](size_t index) const
{
    if (index >= _size)
        throw MatrixOutOfRange();

    return _row[index];
}

template <ConvertibleToDouble T>
void Matrix<T>::MatrixRow::reset()
{
    _size = 0;
    _row.reset();
}

template <ConvertibleToDouble T>
void Matrix<T>::MatrixRow::reset(T *row, size_t size)
{
    _size = size;
    _row = row;
}

#endif //LAB_03_MATRIXROW_HPP
