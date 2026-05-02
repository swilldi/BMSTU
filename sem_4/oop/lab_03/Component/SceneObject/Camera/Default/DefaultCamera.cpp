//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "DefaultCamera.h"

DefaultCamera::DefaultCamera() : _viewpoint(0, 0, 500), _up(Vector3D<double>::up()),
    _right(Vector3D<double>::right()), _forward(Vector3D<double>::forward()), _fov(90), _near(0.1), _far(100.0) { }

DefaultCamera::DefaultCamera(const Point &point) : _viewpoint(point) { }

const Matrix<double> DefaultCamera::get_look_matrix() const noexcept
{
    Vector3D<double> forward = _forward.normalized();
    Vector3D<double> right = _forward.cross(_up).normalized();
    Vector3D<double> up = right.cross(forward);

    Matrix<double> look_matrix(4, 4, 0);

    look_matrix[0][0] = right.get_x();
    look_matrix[1][0] = right.get_y();
    look_matrix[2][0] = right.get_z();

    look_matrix[0][1] = up.get_x();
    look_matrix[1][1] = up.get_y();
    look_matrix[2][1] = up.get_z();

    look_matrix[0][2] = -forward.get_x();
    look_matrix[1][2] = -forward.get_y();
    look_matrix[2][2] = -forward.get_z();

    look_matrix[0][3] = -right.dot(_viewpoint);
    look_matrix[1][3] = -up.dot(_viewpoint);
    look_matrix[2][3] = forward.dot(_viewpoint);

    return look_matrix;
}

const Matrix<double> DefaultCamera::get_projection_matrix(double ratio) const
{
    Matrix<double> projection_matrix(4, 4, 0);

    double fov_radian =_fov * M_PI / 180;
    double tg_half_fov = tan(fov_radian / 2);

    projection_matrix[0][0] = 1 / (ratio * tg_half_fov);
    projection_matrix[1][1] = 1 / tg_half_fov;
    projection_matrix[2][2] = -(_far + _near) / (_far - _near);
    projection_matrix[2][3] = -2.0 * _far * _near / (_far - _near);
    projection_matrix[3][2] = -1;

    return projection_matrix;
}

Point DefaultCamera::get_center() const noexcept
{
    return _viewpoint;
}

void DefaultCamera::transform(const std::shared_ptr<const TransformAction> action)
{
    if (action->is_move_action())
    {
        action->transform(_viewpoint);
    }
    else
    {
        const auto &transform_matrix = action->get_matrix();
        Matrix<double> rotation_matrix(3, 3);
        for (size_t i = 0; i < 3; ++i)
            for (size_t j = 0; j < 3; ++j)
                rotation_matrix[i][j] = transform_matrix[i][j];

        _forward = (rotation_matrix *_forward).normalized();
        _right = (rotation_matrix *_right).normalized();
        _up = (rotation_matrix *_up).normalized();

        _right = _forward.cross(_up).normalized();
        _up = _right.cross(_forward).normalized();
    }
}

void DefaultCamera::accept(std::shared_ptr<BaseVisitor> visitor)
{
    visitor->visit(*this);
}
