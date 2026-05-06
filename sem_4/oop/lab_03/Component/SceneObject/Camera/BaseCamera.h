//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASECAMERA_H
#define LAB_03_BASECAMERA_H
#include "Component/SceneObject/SceneObject.h"
#include "Implementor/BaseCameraImpl.h"
#include "Transform/Action/TransformAction.h"

class BaseCamera : public SceneObject
{
public:
    BaseCamera() = default;
    explicit BaseCamera(std::shared_ptr<BaseCameraImpl> impl) : _impl(impl) { }
    ~BaseCamera() override = default;

    const Matrix<double> get_look_matrix() const noexcept;
    const Matrix<double> get_projection_matrix(double ration) const;
    Point get_center() const noexcept override;
    void transform(const std::shared_ptr<const TransformAction> action);

    bool is_visible() const noexcept override { return false; }
    void accept(std::shared_ptr<BaseVisitor> visitor) override;

protected:
    std::shared_ptr<BaseCameraImpl> _impl;
};

#endif //LAB_03_BASECAMERA_H