//
// Created by Dmitriy Dudurev on 03.05.2026.
//

#ifndef LAB_03_BUILDERCREATOR_HPP
#define LAB_03_BUILDERCREATOR_HPP

#include "BuilderCreator.h"

template <typename BaseBuilder, Derivative<BaseBuilder> DeriveBuilder, typename... Args>
    requires ConstructableWith<DeriveBuilder, Args...>
template <typename... CallArgs> requires (IsSupportedArgs<CallArgs, Args...> && ...)
std::shared_ptr<BaseBuilder> BuilderCreator<BaseBuilder, DeriveBuilder, Args...>::create(CallArgs &&... args)
{
    return std::make_shared<DeriveBuilder>(std::forward<CallArgs>(args)...);
}


#endif //LAB_03_BUILDERCREATOR_HPP