//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BONEMODELBUILDER_H
#define LAB_03_BONEMODELBUILDER_H
#include "Builders/Model/BaseModelBuilder.h"
#include "Component/SceneObject/Model/Structure/List/ListStructure.h"


class BoneModelBuilder : public BaseModelBuilder
{
public:
    BoneModelBuilder() = delete;
    explicit BoneModelBuilder(std::shared_ptr<ModelReader> reader);

    virtual ~BoneModelBuilder() override = default;

    bool build_points() override;
    bool build_edges() override;
    bool build_center() override;

    std::shared_ptr<BaseModelImpl> create_product() override;

private:
    std::shared_ptr<BaseModelImpl> _impl;
};


#endif //LAB_03_BONEMODELBUILDER_H
