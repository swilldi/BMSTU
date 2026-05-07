//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_BASEMODEL_H
#define LAB_03_BASEMODEL_H
#include "Component/SceneObject/SceneObject.h"
#include "Component/SceneObject/Model/Structure/BaseStructure.h"


class BaseModel : public SceneObject
{
public:
    BaseModel() = default;

    explicit BaseModel(std::shared_ptr<BaseModelImpl> impl) : _impl(impl) {}

    virtual ~BaseModel() override = default;

    bool is_visible() const noexcept override { return true; }

protected:
    std::shared_ptr<BaseModelImpl> _impl;
};

#endif //LAB_03_BASEMODEL_H
