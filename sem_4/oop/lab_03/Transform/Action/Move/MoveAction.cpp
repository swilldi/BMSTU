//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "MoveAction.h"
#include "Transform/Data/Move/MoveData.h"

MoveAction::MoveAction(const MoveData &data) noexcept : TransformAction()
{
    _matrix[0][3] = data.get_dx();
    _matrix[1][3] = data.get_dy();
    _matrix[2][3] = data.get_dz();
}

bool MoveAction::is_move_action() const noexcept
{
    return true;
}

