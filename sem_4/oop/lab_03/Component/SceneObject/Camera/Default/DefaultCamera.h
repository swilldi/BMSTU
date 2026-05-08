//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DEFAULTCAMERA_H
#define LAB_03_DEFAULTCAMERA_H

#include "Component/SceneObject/Camera/BaseCamera.h"
#include "Component/SceneObject/Camera/Implementor/BaseCameraImpl.h"

class DefaultCamera final : public BaseCamera
{
public:
    DefaultCamera() = delete;
    explicit DefaultCamera(std::shared_ptr<BaseCameraImpl> impl);
    ~DefaultCamera() override = default;

    Point get_center() const noexcept override;
    void accept(std::shared_ptr<BaseVisitor> visitor) override;

private:
    std::shared_ptr<BaseCameraImpl> _impl;
};

#endif //LAB_03_DEFAULTCAMERA_H
