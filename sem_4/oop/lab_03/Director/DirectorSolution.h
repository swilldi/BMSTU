//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_DIRECTORSOLUTION_H
#define LAB_03_DIRECTORSOLUTION_H
#include "BaseDirector.h"

#include <functional>
#include <map>
#include <Concepts/Concepts.h>

template <typename... SupportedArgs>
class DirectorSolution
{
public:
    DirectorSolution() = default;

    ~DirectorSolution() = default;

    template <Derivative<BaseModelDirector> Derived, typename... Args> requires
        (IsSupportedArgs<Args, SupportedArgs...> && ...) && ConstructableWith<Derived, Args...>
    void registrate(size_t id);

    template <typename ... Args> requires (IsSupportedArgs<Args, SupportedArgs...> && ...)
    std::unique_ptr<BaseModelDirector> create(size_t id, Args && ...);

private:
    using CreatorFunction = std::function<std::unique_ptr<BaseModelDirector>(
        const std::tuple<SupportedArgs...> &)>;
    std::map<size_t, CreatorFunction> _creators;
};

#include "DirectorSolution.hpp"

using BaseDirectorSolution = DirectorSolution<std::shared_ptr<BaseBuilder<BaseModelImpl>>>;

#endif //LAB_03_DIRECTORSOLUTION_H
