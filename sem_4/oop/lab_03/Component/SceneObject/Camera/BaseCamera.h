//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASECAMERA_H
#define LAB_03_BASECAMERA_H
#include "Component/SceneObject/SceneObject.h"

class TransformAction;

class BaseCamera : public SceneObject
{
public:
    BaseCamera() = default;
    ~BaseCamera() override = default;

    Point get_center() const noexcept override = 0;
    bool is_visible() const noexcept override { return false; }
    void accept(std::shared_ptr<BaseVisitor> visitor) override = 0;
};

#endif //LAB_03_BASECAMERA_H
