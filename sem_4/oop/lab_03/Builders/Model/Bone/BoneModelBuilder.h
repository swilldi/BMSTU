//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BONEMODELBUILDER_H
#define LAB_03_BONEMODELBUILDER_H
#include "Builders/Model/BaseModelBuilder.h"


class BoneModelBuilder : public BaseModelBuilder
{
public:
    BoneModelBuilder() = delete;
    BoneModelBuilder(std::shared_ptr<ModelReader> reader, std::shared_ptr<BaseStructure> structure);

    virtual ~BoneModelBuilder() override = default;

    bool build_points() override;
    bool build_edges() override;
    bool build_center() override;

    std::shared_ptr<BaseObject> create_product() override;

private:
    std::shared_ptr<BaseStructure> _structure;
};


#endif //LAB_03_BONEMODELBUILDER_H