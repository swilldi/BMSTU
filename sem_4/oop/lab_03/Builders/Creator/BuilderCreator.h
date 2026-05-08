//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BUILDERCREATOR_H
#define LAB_03_BUILDERCREATOR_H

#include "Builders/BaseBuilder.h"
#include "Builders/Model/List/ListBoneModelBuilder.h"
#include "Builders/Model/Matrix/MatrixBoneModelBuilder.h"
#include "Concepts/Concepts.h"

#include <memory>

template <typename BaseBuilder, Derivative<BaseBuilder> DeriveBuilder, typename ... Args>
    requires ConstructableWith<DeriveBuilder, Args ...>
class BuilderCreator
{
public:
    BuilderCreator() = default;
    ~BuilderCreator() = default;

    template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseBuilder> create(CallArgs && ... args);
};

#include "BuilderCreator.hpp"

using BoneBuilderCreator =
    BuilderCreator<BaseModelBuilder, ListBoneModelBuilder, std::shared_ptr<ModelReader>>;

using MatrixBuilderCreator =
    BuilderCreator<BaseModelBuilder, MatrixBoneModelBuilder, std::shared_ptr<ModelReader>>;

#endif //LAB_03_BUILDERCREATOR_H
