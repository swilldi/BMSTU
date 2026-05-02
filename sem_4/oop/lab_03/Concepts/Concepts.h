//
// Created by Dmitriy Dudurev on 29.04.2026.
//

#ifndef LAB_03_CONCEPTS_H
#define LAB_03_CONCEPTS_H

#include <concepts>

template <typename Derive, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derive>;

template <typename T, typename ... Args>
concept ConstructableWith = requires(Args && ... args)
{
    T { std::forward<Args>(args)... };
};

template <typename T, typename ... Args>
concept IsSupportedArgs = (std::is_convertible_v<T, Args> || ...);

template <typename T>
concept ConvertibleToDouble = std::convertible_to<T, double>;

#endif //LAB_03_CONCEPTS_H