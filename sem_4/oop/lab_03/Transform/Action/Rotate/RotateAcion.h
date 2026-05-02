//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_ROTATEACION_H
#define LAB_03_ROTATEACION_H
#include "Transform/Action/TransformAction.h"
#include "Transform/Data/Rotate/RotateData.h"


class RotateAction : public TransformAction
{
public:
    RotateAction() = default;
    RotateAction(const RotateData &data);

    virtual ~RotateAction() override = default;

    bool is_move_action() const noexcept override;

private:
    Matrix<double> create_rotation_by_x(double angle);
    Matrix<double> create_rotation_by_y(double angle);
    Matrix<double> create_rotation_by_z(double angle);
};

#endif //LAB_03_ROTATEACION_H