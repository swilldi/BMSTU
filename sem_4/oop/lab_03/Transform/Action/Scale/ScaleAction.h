//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_SCALE_H
#define LAB_03_SCALE_H
#include "Transform/Action/TransformAction.h"
#include "Transform/Data/Scale/ScaleData.h"

class ScaleAction : public TransformAcction
{
public:
    ScaleAction() = default;
    ScaleAction(const ScaleData &data);

    virtual ~ScaleAction() override = default;

    bool is_move_action() const noexcept override;
};

#endif //LAB_03_SCALE_H