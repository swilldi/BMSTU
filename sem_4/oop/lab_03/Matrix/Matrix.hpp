//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_MATRIX_HH
#define LAB_03_MATRIX_HH

#include <vector>
#include "Concepts/Concepts.h"
#include "Exceptions/Matrix/MatrixExceptions.h"
#include "Matrix.h"

template <ConvertibleToDouble T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows(rows), _cols(cols)
{
    _matrix = alloc_matrix(rows, cols);
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &filler) : Matrix(rows, cols)
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            _matrix[i][j] = filler;
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T> > list)
{
    size_t rows_count = list.size();
    auto it = list.begin();
    size_t cols_count = it->size();

    for (const auto &row : list)
        if (row.size() != cols_count)
            throw MatrixInitListInvalidSize();

    _rows = rows_count;
    _cols = cols_count;
    _matrix = alloc_matrix(rows_count, cols_count);
    size_t i = 0;
    for (const auto &row : list)
    {
        for (const auto &elem : row)
        {
            _matrix[i / cols_count][i % cols_count] = elem;
            ++i;
        }
    }
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<T> > list)
{
    *this = Matrix(list);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(const Matrix<T> &other) : Matrix(other._rows, other._cols)
{
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _matrix[i][j] = other[i][j];
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
{
    *this = Matrix(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept
{
    _rows = other._rows;
    _cols = other._cols;
    _matrix = std::move(other._matrix);
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept
{
    if (this != &other)
    {
        _rows = other._rows;
        _cols = other._cols;
        _matrix = std::move(other._matrix);
    }
}

// === Информация о матрице ===
template <ConvertibleToDouble T>
size_t Matrix<T>::cols() const noexcept
{
    return _cols;
}

template <ConvertibleToDouble T>
size_t Matrix<T>::rows() const noexcept
{
    return _rows;
}

// === Операции над матрицей ===
// Сложение
template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::add(const Matrix<T> &other)
{
    if (_rows != other._rows || _cols != other._cols)
        throw MatrixIncompatibleDimensions();

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _matrix[i][j] += other[i][j];

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &other)
{
    add(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::sum(const Matrix<T> &other) const
{
    if (_rows != other._rows || _cols != other._cols)
        throw MatrixIncompatibleDimensions();

    Matrix<T> tmp = Matrix(*this);
    tmp.add(other);
    return tmp;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    return sum(other);
}

// Вычитание
template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::subtract(const Matrix<T> &other)
{
    if (_rows != other._rows || _cols != other._cols)
        throw MatrixIncompatibleDimensions();

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _matrix[i][j] -= other[i][j];

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &other)
{
    subtract(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::diff(const Matrix<T> &other) const
{
    Matrix<T> tmp = Matrix(*this);
    tmp.subtract(other);
    return tmp;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const
{
    return diff(other);
}

// Умножение матриц
template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::multiply(const Matrix<T> &other)
{
    *this = product(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &other)
{
    multiply(other);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::product(const Matrix<T> &other) const
{
    if (_cols != other._rows)
        throw MatrixIncompatibleDimensions();

    Matrix<T> tmp(_rows, other._cols, 0);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < other._cols; ++j)
            for (size_t k = 0; k < _cols; ++k)
                tmp[i][j] += _matrix[i][k] * other[k][j];

    return tmp;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
{
    return product(other);
}


// Умножение матрицы на элемент
template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::multiply(const T &elem) noexcept
{
    if (_rows != other._rows || _cols != other._cols)
        throw MatrixIncompatibleDimensions();

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _matrix[i][j] *= elem;

    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> &Matrix<T>::operator*=(const T &elem) noexcept
{
    multiply(elem);
    return *this;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::product(const T &elem) const
{
    Matrix<T> tmp(*this);
    tmp.multiply(elem);
    return tmp;
}

template <ConvertibleToDouble T>
Matrix<T> Matrix<T>::operator*(const T &elem) const
{
    return product(elem);
}

// Умножение матрицы на вектор
template <ConvertibleToDouble T>
Vector3D<T> Matrix<T>::product(const Vector3D<T> &other) const
{
    Matrix<T> tmp(3, 1);
    tmp[0][0] = other.get_x();
    tmp[1][0] = other.get_y();
    tmp[2][0] = other.get_z();

    Matrix<T> result = product(tmp);
    return Vector3D<T>(result[0][0], result[1][0], result[2][0]);
}

template <ConvertibleToDouble T>
Vector3D<T> Matrix<T>::operator*(const Vector3D<T> &other) const
{
    return product(other);
}

// === Доступ к элементам матрицы ===
template <ConvertibleToDouble T>
Matrix<T>::MatrixRow &Matrix<T>::operator[](size_t index) {
    if (index >= _rows)
        throw MatrixOutOfRange();

    return _matrix[index];
}

template <ConvertibleToDouble T>
const Matrix<T>::MatrixRow &Matrix<T>::operator[](size_t index) const {
    if (index >= _rows)
        throw MatrixOutOfRange();

    return _matrix[index];
}

template <ConvertibleToDouble T>
std::shared_ptr<typename Matrix<T>::MatrixRow[]> Matrix<T>::alloc_matrix(size_t row, size_t col)
{
    std::shared_ptr<MatrixRow[]> matrix;
    try
    {
        matrix = std::make_shared<MatrixRow[]>(row);
        for (size_t i = 0; i < row; ++i)
            matrix[i].reset(std::make_shared<T[]>(col), col);
    }
    catch (std::bad_alloc &e)
    {
        throw MatrixMemoryAllocateError();
    }
    return matrix;
}

#endif //LAB_03_MATRIX_HH
