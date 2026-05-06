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
    DefaultCamera(std::shared_ptr<BaseCameraImpl> impl) : BaseCamera(impl) { }

};

#endif //LAB_03_DEFAULTCAMERA_H