//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DIRECTORSOLUTION_HPP
#define LAB_03_DIRECTORSOLUTION_HPP

#include "Concepts/Concepts.h"
#include "DirectorSolution.h"

template <typename... SupportedArgs>
template <Derivative<BaseDirector> Derived, typename... Args> requires
    (IsSupportedArgs<Args, SupportedArgs...> && ...) && ConstructableWith<Derived, Args...>
void DirectorSolution<SupportedArgs...>::registrate(size_t id)
{
    _creators[id] = [](const std::tuple<SupportedArgs...> &args) {
        return std::apply([](auto &&...args)
            { return std::make_unique<Derived>(std::forward<decltype(args)>(args)...);}, args);
    };
}

template <typename... SupportedArgs>
template <typename... Args>
    requires(IsSupportedArgs<Args, SupportedArgs...> && ...)
std::unique_ptr<BaseDirector> DirectorSolution<SupportedArgs...>::create(size_t id, Args &&...args)
{
    auto it = _creators.find(id);
    if (it != _creators.end())
        return it->second(std::make_tuple(std::forward<Args>(args)...));

    return nullptr;
}



#endif //LAB_03_DIRECTORSOLUTION_HPP
