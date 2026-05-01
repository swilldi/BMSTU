//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_BONEMODEL_H
#define LAB_03_BONEMODEL_H

#include "Component/SceneObject/Model/BaseModel.h"
#include "Component/SceneObject/Model/Structure/BaseStructure.h"

class BoneModel final : public BaseModel
{
public:
    BoneModel() = default;
    explicit BoneModel(std::shared_ptr<BaseStructure> structure);

    virtual ~BoneModel() override = default;

    Point get_center() const noexcept override;
    std::shared_ptr<BaseStructure> get_structure() const override;

    void accept(std::shared_ptr<BaseVisitor> visitor) override;
};

#endif //LAB_03_BONEMODEL_H
