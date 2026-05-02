//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DEFAULTCAMERA_H
#define LAB_03_DEFAULTCAMERA_H

#include "Component/SceneObject/Camera/BaseCamera.h"
#include "Vector3D/Vector3D.h"
#include "Visitor/BaseVisitor.h"

class DefaultCamera final : public BaseCamera
{
public:
    DefaultCamera();
    DefaultCamera(const Point &point);

    virtual ~DefaultCamera() override = default;

    const Matrix<double> get_look_matrix() const noexcept override;
    const Matrix<double> get_projection_matrix(double ratio) const override;
    Point get_center() const noexcept override;

    void transform(const std::shared_ptr<const TransformAction> action) override;
    void accept(std::shared_ptr<BaseVisitor> visitor) override;

private:
    Point _viewpoint;
    Vector3D<double> _up, _right, _forward;
    double _fov, _near, _far;


};

#endif //LAB_03_DEFAULTCAMERA_H