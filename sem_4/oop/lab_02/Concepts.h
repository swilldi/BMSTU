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

template <typename T, typename U>
concept ConvertableContainerValue = ContainerValue<U> && Convertible<U, T>;

template <typename T, typename U>
concept EquatableContainerValue = ContainerValue<U> && Equatable<U, T>;

template <typename C>
concept Container = requires(C c)
{
    typename C::value_type;
    typename C::const_iterator;
    typename C::iterator;
    typename C::size_type;

    { c.begin() } -> std::same_as<typename C::iterator>;
    { c.end() } -> std::same_as<typename C::iterator>;
    { c.cbegin() } -> std::same_as<typename C::const_iterator>;
    { c.cend() } -> std::same_as<typename C::const_iterator>;

    { c.size() } -> std::same_as<typename C::size_type>;
    { c.empty() } -> std::same_as<bool>;
};

template <typename T, typename U>
concept CommonType = requires { typename std::common_type<T, U>; };

template <typename C, typename T>
concept ConvertableContainer = Container<C> && Convertible<typename C::value_type, T>;


template <typename C, typename T>
concept EquatableContainer = Container<C> && Equatable<typename C::value_type, T> &&
                             CommonType<typename C::value_type, T>;

template <typename I>
concept InputIterator = std::input_iterator<I>;

template <typename I>
concept ForwardIterator = std::forward_iterator<I>;

template <typename I, typename T>
concept ConvertableForwardIterator = ForwardIterator<I> && Convertible<std::iter_value_t<I>, T>;


template <typename C, typename T>
concept CommonContainer = Container<C> && CommonType<typename C::value_type, T>;


template <ContainerValue T>
class Set;

template <typename C>
concept IsSet = std::same_as<Set<typename C::value_type>, C>;

template <typename C, typename T>
concept NotSetConvertableContainer = ConvertableContainer<C, T> && !IsSet<C>;

template <typename C, typename T>
concept NotSetCommonContainer = CommonContainer<C, T> && !IsSet<C>;

template <typename C, typename T>
concept NotSetEquatableContainer = EquatableContainer<C, T> && !IsSet<C>;

template <typename S, typename I>
concept Sentinel = std::sentinel_for<S, I>;

template <typename R>
concept Range = std::ranges::input_range<R> && !Container<R>;

template <typename R, typename T>
concept ConvertibleRange = Range<R> && Convertible<std::ranges::range_value_t<R>, T>;

#endif //LAB_02_CONCEPTS_H
