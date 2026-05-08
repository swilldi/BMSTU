//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_REMOVEINVISIBLEEDGECREATOR_HPP
#define LAB_03_REMOVEINVISIBLEEDGECREATOR_HPP

template <typename BaseRemoveInvisibleEdge, Derivative<BaseRemoveInvisibleEdge> DeriveRemoveInvisibleEdge, typename ... Args>
    requires ConstructableWith<DeriveRemoveInvisibleEdge, Args ...>
template <typename ... CallArgs> requires (IsSupportedArgs<CallArgs, Args ...> && ...)
std::shared_ptr<BaseRemoveInvisibleEdge> RemoveInvisibleEdgeCreator<BaseRemoveInvisibleEdge,
    DeriveRemoveInvisibleEdge, Args ...>::create(CallArgs && ... args)
{
    return std::make_shared<DeriveRemoveInvisibleEdge>(std::forward<CallArgs>(args)...);
}

#endif //LAB_03_REMOVEINVISIBLEEDGECREATOR_HPP