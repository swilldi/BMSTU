//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "ScaleAction.h"
#include "Transform/Action/Move/MoveAction.h"
#include "Transform/Data/Scale/ScaleData.h"

ScaleAction::ScaleAction(const ScaleData &data) : TransformAcction()
{
    MoveAction to_center({ -data.get_center_x(), -data.get_center_y(), -data.get_center_z() });
    _matrix *= to_center.get_matrix();

    Matrix<double> scale_matrix(4, 4,0);
    scale_matrix[0][0] = data.get_kx();
    scale_matrix[1][1] = data.get_ky();
    scale_matrix[2][2] = data.get_kz();

    _matrix *= scale_matrix;

    MoveAction from_center({ data.get_center_x(), data.get_center_y(), data.get_center_z() });
    _matrix *= from_center.get_matrix();
}

bool ScaleAction::is_move_action() const noexcept
{
    return false;
}
