//
// Created by Dmitriy Dudurev on 08.05.2026.
//

#ifndef LAB_03_MATRIXBONEMODELBUILDER_H
#define LAB_03_MATRIXBONEMODELBUILDER_H

#include "Builders/Model/BaseModelBuilder.h"
#include "Component/SceneObject/Model/Implementor/Matrix/MatrixModelImpl.h"

class MatrixBoneModelBuilder final : public BaseModelBuilder
{
public:
    using BaseModelBuilder::BaseModelBuilder;
    virtual ~MatrixBoneModelBuilder() override = default;

protected:
    std::shared_ptr<BaseModelImpl> create_impl() override
    {
        return std::make_shared<MatrixModelImpl>();
    }
};

#endif //LAB_03_MATRIXBONEMODELBUILDER_H
