//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BaseCamera.h"

const Matrix<double> BaseCamera::get_look_matrix() const noexcept
{
    return _impl->get_look_matrix();
}
const Matrix<double> BaseCamera::get_projection_matrix(double ration) const
{
    return _impl->get_projection_matrix(ration);
}
void BaseCamera::transform(const std::shared_ptr<const TransformAction> action)
{
    return _impl->transform(action);
}

Point BaseCamera::get_center() const noexcept
{
    return _impl->get_center();
}

void BaseCamera::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(*this);
}

