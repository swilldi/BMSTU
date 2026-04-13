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
concept Convertable = std::convertible_to<From, To> || std::same_as<From, To>;

template <typename T>
concept CopyAssingable = requires(T &t1, T &t2)
{
    t1 = t2;
};

template <typename T>
concept MoveAssingale = requires(T &t1, T &t2)
{
    t1 = std::move(t2);
};

template <typename T>
concept Assingable = CopyAssingable<T> && MoveAssingale<T>;

template <typename T>
concept CopyMoveAssingable = std::copy_constructible<T> &&
                             std::move_constructible<T> &&
                             Assingable<T>;

template <typename T, typename U>
concept Equatable = requires(T t, U u)
{
    { t == u } -> std::same_as<bool>;
    { u == t } -> std::same_as<bool>;
    { t != u } -> std::same_as<bool>;
    { u != t } -> std::same_as<bool>;
};

template <typename T>
concept ContainerValue = Equatable<T, T> && CopyMoveAssingable<T>;

template <typename C>
concept Container = CopyMoveAssingable<C> && requires(C c)
{
    typename C::value_type;
    typename C::reference;
    typename C::const_reference;
    typename C::pointer;
    typename C::const_iterator;
    typename C::size_type;
    typename C::difference_type;

    { c.begin() } -> std::same_as<typename C::reference>;
    { c.end() } -> std::same_as<typename C::reference>;

    { c.size() } -> std::same_as<typename C::size_type>;
    { c.empty() } -> std::same_as<bool>;
};

template <typename T>
concept InputIterator = std::input_iterator<T>;

template <typename T>
concept ForwardIterator = std::forward_iterator<T>;

template <typename S, typename I>
concept Sentinel = std::sentinel_for<S, I>;


#endif //LAB_02_CONCEPTS_H
