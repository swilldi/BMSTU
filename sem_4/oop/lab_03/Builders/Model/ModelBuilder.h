//
// Created by Dmitriy Dudurev on 07.05.2026.
//

#ifndef LAB_03_MODELBUILDER_H
#define LAB_03_MODELBUILDER_H

#include "Builders/Model/BaseModelBuilder.h"
#include "Component/SceneObject/Model/Implementor/List/ListModelImpl.h"
#include "Component/SceneObject/Model/Implementor/Matrix/MatrixModelImpl.h"
#include "Concepts/Concepts.h"

template <Derivative<BaseModelImpl> Impl>
class ModelBuilder : public BaseModelBuilder
{
public:
    ModelBuilder() = delete;
    explicit ModelBuilder(std::shared_ptr<ModelReader> reader);

    virtual ~ModelBuilder() override = default;

    bool build_points() override;
    bool build_edges() override;
    bool build_center() override;

    std::shared_ptr<BaseModelImpl> create_product() override;

private:
    std::shared_ptr<BaseModelImpl> _impl;
};

#include "ModelBuilder.hpp"

using BoneModelBuilder   = ModelBuilder<ListModelImpl>;
using MatrixModelBuilder = ModelBuilder<MatrixModelImpl>;

#endif //LAB_03_MODELBUILDER_H
