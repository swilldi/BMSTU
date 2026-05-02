//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_REMOVEINVISIBLEEDGECREATOR_H
#define LAB_03_REMOVEINVISIBLEEDGECREATOR_H

#include "Concepts/Concepts.h"
#include "Strategies/RemoveInvisibleEdge/BaseRemoveInvisibleEdge.h"
#include "Strategies/RemoveInvisibleEdge/RayCasting/RayCastingRemoveInvisibleEdge.h"

#include <memory>

template <typename BaseRemoveInvisibleEdge, Derivative<BaseRemoveInvisibleEdge> DeriveRemoveInvisibleEdge, typename ... Args>
    requires ConstructableWith<DeriveRemoveInvisibleEdge, Args ...>
class RemoveInvisibleEdgeCreator
{
public:
    RemoveInvisibleEdgeCreator() = default;
    ~RemoveInvisibleEdgeCreator() = default;

    template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
    static std::shared_ptr<BaseRemoveInvisibleEdge> create(CallArgs && ... args);
};

#include "RemoveInvisibleEdgeCreator.hpp"

using RayCastingRemoveInvisibleEdgeCreator = RemoveInvisibleEdgeCreator<BaseRemoveInvisibleEdge, RayCastingRemoveInvisibleEdge>;

#endif //LAB_03_REMOVEINVISIBLEEDGECREATOR_H