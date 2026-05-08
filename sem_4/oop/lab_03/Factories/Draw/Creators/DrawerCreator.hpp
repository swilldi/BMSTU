//
// Created by Dmitriy Dudurev on 06.05.2026.
//

#ifndef LAB_03_DRAWERCREATOR_HPP
#define LAB_03_DRAWERCREATOR_HPP

#include "DrawerCreator.h"

#include <memory>
#include <utility>

template <typename BaseDrawer, Derivative<BaseDrawer> DeriveDrawer, typename... Args> requires ConstructableWith<DeriveDrawer, Args...>
template <typename... CallArgs> requires (IsSupportedArgs<CallArgs, Args...> && ...)
std::shared_ptr<BaseDrawer> DrawerCreator<BaseDrawer, DeriveDrawer, Args...>::create(CallArgs &&... args)
{
    return std::make_shared<DeriveDrawer>(std::forward<CallArgs>(args)...);
}

#endif //LAB_03_DRAWERCREATOR_HPP
