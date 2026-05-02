//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_MOVEACTION_H
#define LAB_03_MOVEACTION_H
#include "Transform/Action/TransformAction.h"
#include "Transform/Data/Move/MoveData.h"

class MoveAction : public TransformAction
{
public:
    MoveAction() = default;
    virtual ~MoveAction() = default;
    MoveAction(const MoveData &data) noexcept;

    bool is_move_action() const noexcept override;
};

#endif //LAB_03_MOVEACTION_H