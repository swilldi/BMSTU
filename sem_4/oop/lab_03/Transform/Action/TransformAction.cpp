//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "TransformAction.h"

TransformAction::TransformAction() : _matrix(4, 4, 0)
{
    for (size_t i = 0; i < 4; ++i)
        _matrix[i][i] = 1.0;
}

Matrix<double> &TransformAction::get_matrix() noexcept
{
    return _matrix;
}

const Matrix<double> &TransformAction::get_matrix() const noexcept
{
    return _matrix;
}

Point &TransformAction::transform(Point &point) const noexcept
{
    point.transform(_matrix);
    return point;
}
