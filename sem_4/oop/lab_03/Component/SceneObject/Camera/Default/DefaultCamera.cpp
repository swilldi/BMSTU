//
// Created by Dmitriy Dudurev on 06.05.2026.
//

#include "DefaultCamera.h"

DefaultCamera::DefaultCamera(std::shared_ptr<BaseCameraImpl> impl) : _impl(impl) { }

// const Matrix<double> DefaultCamera::get_look_matrix() const noexcept
// {
//     return _impl->get_look_matrix();
// }
//
// const Matrix<double> DefaultCamera::get_projection_matrix(double ratio) const
// {
//     return _impl->get_projection_matrix(ratio);
// }
//
// void DefaultCamera::transform(const std::shared_ptr<const TransformAction> action)
// {
//     _impl->transform(action);
// }

Point DefaultCamera::get_center() const noexcept
{
    return _impl->get_center();
}

void DefaultCamera::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(_impl);
}
