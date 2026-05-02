//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_PROJECTIONCREATOR_H
#define LAB_03_PROJECTIONCREATOR_H

#include "Concepts/Concepts.h"
#include "Strategies/Projection/BaseProjection.h"

#include <memory>

template <typename BaseProjection, Derivative<BaseProjection> DeriveProjection, typename ... Args>
    requires ConstructableWith<DeriveProjection, Args ...>
class ProjectionCreator
{
    ProjectionCreator() = default;
    ~ProjectionCreator() = default;

    template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args...> && ...)
    static std::shared_ptr<BaseProjection> create(CallArgs && ... args);
};

#include "ProjectionCreator.hpp"


#endif //LAB_03_PROJECTIONCREATOR_H