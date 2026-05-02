//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_PROJECTIONCREATOR_HPP
#define LAB_03_PROJECTIONCREATOR_HPP

template <typename BaseProjection, Derivative<BaseProjection> DeriveProjection, typename... Args>
    requires ConstructableWith<DeriveProjection, Args...>
template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args...> && ...)
std::shared_ptr<BaseProjection> ProjectionCreator<BaseProjection, DeriveProjection, Args...>::create(
    CallArgs &&... args)
{
    return std::make_shared<DeriveProjection>(std::forward<CallArgs>(args)...);
}

#endif //LAB_03_PROJECTIONCREATOR_HPP
