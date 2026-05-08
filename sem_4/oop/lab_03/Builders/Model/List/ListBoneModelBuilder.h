//
// Created by Dmitriy Dudurev on 08.05.2026.
//

#ifndef LAB_03_LISTBONEMODELBUILDER_H
#define LAB_03_LISTBONEMODELBUILDER_H

#include "Builders/Model/BaseModelBuilder.h"
#include "Component/SceneObject/Model/Implementor/List/ListModelImpl.h"

class ListBoneModelBuilder final : public BaseModelBuilder
{
public:
    using BaseModelBuilder::BaseModelBuilder;
    virtual ~ListBoneModelBuilder() override = default;

protected:
    std::shared_ptr<BaseModelImpl> create_impl() override
    {
        return std::make_shared<ListModelImpl>();
    }
};

#endif //LAB_03_LISTBONEMODELBUILDER_H
