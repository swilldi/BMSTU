//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEPROJECTION_H
#define LAB_03_BASEPROJECTION_H
#include "Component/SceneObject/Camera/BaseCamera.h"
#include "Component/SceneObject/Model/Structure/BaseStructure.h"

#include <memory>

class BaseProjection
{
public:
    BaseProjection() = default;
    virtual ~BaseProjection() = default;

    virtual void project(std::shared_ptr<const BaseStructure> structure, std::shared_ptr<BaseCamera> camera,
        std::vector<Point> &projected);

};

#endif //LAB_03_BASEPROJECTION_H