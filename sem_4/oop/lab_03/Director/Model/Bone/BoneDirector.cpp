//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BoneDirector.h"

#include "Component/SceneObject/Model/Bone/BoneModel.h"
#include "Exceptions/Builder/Model/ModelBuilderException.h"

BoneDirector::BoneDirector(std::shared_ptr<BaseModelBuilder> builder) : _builder(builder) { }

std::shared_ptr<BaseObject> BoneDirector::create() const
{
    if (!_builder->build_points())
        throw ModelBuilderPointsException();
    if (!_builder->build_edges())
        throw ModelBuilderEdgesException();
    if (!_builder->build_center())
        throw ModelBuilderCenterException();

    return std::make_shared<BoneModel>(_builder->get_product());
}
