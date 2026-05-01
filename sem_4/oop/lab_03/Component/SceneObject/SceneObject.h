//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_SCENEOBJECT_H
#define LAB_03_SCENEOBJECT_H
#include "Component/BaseObject.h"

class SceneObject: public BaseObject
{
    SceneObject() = default;
    virtual ~SceneObject() = default;

    bool is_composite() const noexcept override
    {
        return false;
    }
};

#endif //LAB_03_SCENEOBJECT_H