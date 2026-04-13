//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_CONCEPTS_H
#define LAB_02_CONCEPTS_H
#include <concepts>
#include <iterator>

template <typename T, typename U>
concept DeriveFrom = std::is_base_of_v<U, T>;

template <typename From, typename To>
concept Convertible = std::convertible_to<From, To>;

template <typename T>
concept CopyAssignable = requires(T &t1, T &t2)
{
    t1 = t2;
};

template <typename T>
concept MoveAssignable = requires(T &t1, T &t2)
{
    t1 = std::move(t2);
};

template <typename T>
concept Assignable = CopyAssignable<T> && MoveAssignable<T>;

template <typename T>
concept CopyMoveAssignable = std::copy_constructible<T> &&
                             std::move_constructible<T> &&
                             Assignable<T>;

template <typename T, typename U>
concept Equatable = requires(T t, U u)
{
    { t == u } -> std::same_as<bool>;
    { u == t } -> std::same_as<bool>;
    { t != u } -> std::same_as<bool>;
    { u != t } -> std::same_as<bool>;
};

template <typename T>
concept ContainerValue = Equatable<T, T> && CopyMoveAssignable<T>;

template <typename C>
concept Container = requires(C c)
{
    typename C::value_type;
    typename C::reference;
    typename C::const_reference;
    typename C::const_iterator;
    typename C::size_type;
    typename C::difference_type;

    { c.begin() } -> std::same_as<typename C::iterator>;
    { c.end() } -> std::same_as<typename C::iterator>;

    { c.size() } -> std::same_as<typename C::size_type>;
    { c.empty() } -> std::same_as<bool>;
};

template <typename T>
concept InputIterator = std::input_iterator<T>;

template <typename T>
concept ForwardIterator = std::forward_iterator<T>;


#endif //LAB_02_CONCEPTS_H
