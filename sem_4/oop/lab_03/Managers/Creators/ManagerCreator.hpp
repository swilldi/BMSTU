//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_MANAGERCREATOR_HPP
#define LAB_03_MANAGERCREATOR_HPP

#include "Managers/Creators/ManagerCreator.h"

template <typename BaseManager, Derivative<BaseManager> DeriveManager, typename ... Args>
    requires ConstructableWith<DeriveManager, Args ...>
template<typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
std::shared_ptr<DeriveManager> ManagerCreator<BaseManager, DeriveManager, Args ...>::create(CallArgs && ... args)
{
    static std::shared_ptr<DeriveManager> manager;
    if (!manager)
        manager = std::make_shared<DeriveManager>(std::forward<CallArgs>(args)...);

    return manager;
}

#endif //LAB_03_MANAGERCREATOR_HPP