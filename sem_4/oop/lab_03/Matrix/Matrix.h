//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_MATRIX_H
#define LAB_03_MATRIX_H

#include <vector>
#include "Vector3D/Vector3D.h"
#include "Concepts/Concepts.h"

template <ConvertibleToDouble T>
class Matrix
{
public:
    // === Конструкторы ===
    Matrix() = delete;
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, const T &filler);
    Matrix(std::initializer_list<std::initializer_list<T>> ilist);
    Matrix<T> &operator=(std::initializer_list<std::initializer_list<T>> ilist);

    Matrix(const Matrix<T> &other);
    Matrix<T> &operator=(const Matrix<T> &other);

    Matrix(Matrix<T> &&other) noexcept;
    Matrix<T> &operator=(Matrix<T> &&other) noexcept;

    // === Деструкторы ===
    ~Matrix() = default;

    // === Информация о матрице ===
    size_t cols() const noexcept;
    size_t rows() const noexcept;

    // === Операции над матрицей ===
    // Сложение
    Matrix<T> &add(const Matrix<T> &other);
    Matrix<T> &operator+=(const Matrix<T> &other);

    Matrix<T> sum(const Matrix<T> &other) const;
    Matrix<T> operator+(const Matrix<T> &other) const;

    // Вычитание
    Matrix<T> &subtract(const Matrix<T> &other);
    Matrix<T> &operator-=(const Matrix<T> &other);

    Matrix<T> diff(const Matrix<T> &other) const;
    Matrix<T> operator-(const Matrix<T> &other) const;

    // Умножение матриц
    Matrix<T> &multiply(const Matrix<T> &other);
    Matrix<T> &operator*=(const Matrix<T> &other);

    Matrix<T> product(const Matrix<T> &other) const;
    Matrix<T> operator*(const Matrix<T> &other) const;


    // Умножение матрицы на элемент
    Matrix<T> &multiply(const T &elem) noexcept;
    Matrix<T> &operator*=(const T &elem) noexcept;

    Matrix<T> product(const T &elem) const;
    Matrix<T> operator*(const T &elem) const;

    // Умножение матрицы на вектор
    Vector3D<T> product(const Vector3D<T> &other) const noexcept;
    Vector3D<T> operator*(const Vector3D<T> &other) const noexcept;

    // === Доступ к элементам матрицы ===
    Matrix &operator[](size_t row);

    const Matrix &operator[](size_t row) const;

protected:
    class MatrixRow
    {
    public:
        MatrixRow(T *row, const size_t size) : _row(row), _size(size) {}
        MatrixRow() : _row(nullptr), _size(0) {}

        T &operator[](size_t index);

        const T &operator[](size_t index) const;

        void reset();

        void reset(T *row, size_t size);

    private:
        std::shared_ptr<T[]> _row;
        size_t _size;
    };

private:
    std::shared_ptr<T[]> _matrix = nullptr;

    std::shared_ptr<MatrixRow[]> allocMatrix(size_t rows, size_t cols);

    size_t _rows, _cols;
};

#include "Matrix.hpp"
#include "MatrixRow.hpp"

#endif //LAB_03_MATRIX_H
