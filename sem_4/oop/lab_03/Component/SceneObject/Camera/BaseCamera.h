//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASECAMERA_H
#define LAB_03_BASECAMERA_H
#include "Component/SceneObject/SceneObject.h"
#include "Transform/Action/TransformAction.h"

class BaseCamera : public SceneObject
{
public:
    BaseCamera() = default;
    virtual ~BaseCamera() override = default;

    virtual const Matrix<double> get_look_matrix() const noexcept = 0;
    virtual const Matrix<double> get_projection_matrix(double ration) const = 0;
    virtual void transform(const std::shared_ptr<const TransformAction> action) = 0;

    bool is_visible() const noexcept override { return false; }
};

#endif //LAB_03_BASECAMERA_H