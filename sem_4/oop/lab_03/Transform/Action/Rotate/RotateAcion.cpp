//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "RotateAcion.h"

#include "Transform/Action/Move/MoveAction.h"

// TODO мб тут сложение?
RotateAction::RotateAction(const RotateData &data) : TransformAcction()
{
    MoveAction to_center({ -data.get_center_x(), -data.get_center_y(), -data.get_center_z() });
    _matrix *= to_center.get_matrix();

    Matrix<double> rotate_matrix = create_rotation_by_x(data.get_angle_x()) *
                                   create_rotation_by_y(data.get_center_y()) * create_rotation_by_z(
                                       data.get_angle_z());

    _matrix *= rotate_matrix;

    MoveAction from_center({ data.get_center_x(), data.get_center_y(), data.get_center_z() });
    _matrix *= from_center.get_matrix();
}

Matrix<double> RotateAction::create_rotation_by_x(double angle)
{
    Matrix<double> matrix(4, 4, 0);
    matrix[0][0] = 1;
    matrix[1][1] = cos(angle);
    matrix[1][2] = sin(angle);
    matrix[2][1] = -sin(angle);
    matrix[2][2] = cos(angle);
    matrix[3][3] = 1;
}

Matrix<double> RotateAction::create_rotation_by_y(double angle)
{
    Matrix<double> matrix(4, 4, 0);
    matrix[0][0] = cos(angle);
    matrix[0][2] = -sin(angle);
    matrix[1][1] = 1;
    matrix[2][0] = sin(angle);
    matrix[2][2] = cos(angle);
    matrix[3][3] = 1;

    return matrix;
}

Matrix<double> RotateAction::create_rotation_by_z(const double angle)
{
    Matrix<double> matrix(4, 4, 0);
    matrix[0][0] = cos(angle);
    matrix[0][1] = sin(angle);
    matrix[1][0] = -sin(angle);
    matrix[1][1] = cos(angle);
    matrix[2][2] = 1;
    matrix[3][3] = 1;

    return matrix;
}

bool RotateAction::is_move_action() const noexcept
{
    return false;
}