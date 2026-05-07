//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BoneDirector.h"

#include "Builders/Model/BaseModelBuilder.h"
#include "Component/SceneObject/Model/Bone/BoneModel.h"
#include "Exceptions/Builder/Model/ModelBuilderException.h"

BoneDirector::BoneDirector(std::shared_ptr<BaseBuilder<BaseModelImpl>> builder)
{
    _builder = builder;
}

std::shared_ptr<BaseObject> BoneDirector::create() const
{
    auto model_builder = std::dynamic_pointer_cast<BaseModelBuilder>(_builder);
    if (!model_builder)
        return nullptr;

    if (!model_builder->build_points())
        throw ModelBuilderPointsException();
    if (!model_builder->build_edges())
        throw ModelBuilderEdgesException();
    if (!model_builder->build_center())
        throw ModelBuilderCenterException();

    return std::make_shared<BoneModel>(_builder->get_product());
}
