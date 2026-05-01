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

    explicit BaseModel(std::shared_ptr<BaseStructure> structure) : _structure(structure) {}

    virtual ~BaseModel() override = default;

    virtual std::shared_ptr<BaseStructure> get_structure() const = 0;

    bool is_visible() const noexcept override { return true; }

protected:
    std::shared_ptr<BaseStructure> _structure;
};

#endif //LAB_03_BASEMODEL_H
