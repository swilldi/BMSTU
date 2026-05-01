//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_TRANSFORMACTION_H
#define LAB_03_TRANSFORMACTION_H

#include "Component/SceneObject/Model/Point/Point.h"
#include "Matrix/Matrix.h"

class TransformAcction
{
public:
    TransformAcction();
    virtual ~TransformAcction() = default;

    Point &transform(Point &point) const noexcept;

    virtual bool is_move_action() const noexcept = 0;

    Matrix<double> &get_matrix() noexcept;
    const Matrix<double> &get_matrix() const noexcept;

protected:
    Matrix<double> _matrix;
};

#endif //LAB_03_TRANSFORMACTION_H