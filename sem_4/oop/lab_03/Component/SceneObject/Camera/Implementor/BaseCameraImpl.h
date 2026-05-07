//
// Created by Dmitriy Dudurev on 05.05.2026.
//

#ifndef LAB_03_BASECAMERAIMPL_H
#define LAB_03_BASECAMERAIMPL_H
#include "Transform/Action/TransformAction.h"

class BaseCameraImpl
{
public:
    BaseCameraImpl() = default;
    virtual ~BaseCameraImpl() = default;

    virtual const Matrix<double> get_look_matrix() const noexcept = 0;
    virtual const Matrix<double> get_projection_matrix(double ratio) const = 0;
    virtual Point get_center() const noexcept = 0;

    virtual void transform(const std::shared_ptr<const TransformAction> action) = 0;
};

#endif //LAB_03_BASECAMERAIMPL_H