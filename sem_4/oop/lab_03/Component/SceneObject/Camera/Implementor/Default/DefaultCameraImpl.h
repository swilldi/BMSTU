//
// Created by Dmitriy Dudurev on 05.05.2026.
//

#ifndef LAB_03_DEFAULTCAMERAIMPL_H
#define LAB_03_DEFAULTCAMERAIMPL_H
#include "Component/SceneObject/Camera/Implementor/BaseCameraImpl.h"


class DefaultCameraImpl : public BaseCameraImpl
{
public:
    DefaultCameraImpl();
    DefaultCameraImpl(const Point &point);
    ~DefaultCameraImpl() override = default;

    const Matrix<double> get_look_matrix() const noexcept override;
    const Matrix<double> get_projection_matrix(double ratio) const override;
    Point get_center() const noexcept override;

    void transform(const std::shared_ptr<const TransformAction> action) override;

private:
    Point _viewpoint;
    Vector3D<double> _up, _right, _forward;
    double _fov, _near, _far;
};


#endif //LAB_03_DEFAULTCAMERAIMPL_H