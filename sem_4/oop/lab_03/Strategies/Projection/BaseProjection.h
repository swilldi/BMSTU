//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEPROJECTION_H
#define LAB_03_BASEPROJECTION_H
#include "Component/SceneObject/Camera/Implementor/BaseCameraImpl.h"
#include "../../Component/SceneObject/Model/Implementor/BaseModelImpl.h"

#include <memory>

class BaseProjection
{
public:
    BaseProjection() = default;
    virtual ~BaseProjection() = default;

    virtual void project(std::shared_ptr<const BaseModelImpl> structure, std::shared_ptr<BaseCameraImpl> camera,
        std::vector<Point> &projected) = 0;

};

#endif //LAB_03_BASEPROJECTION_H