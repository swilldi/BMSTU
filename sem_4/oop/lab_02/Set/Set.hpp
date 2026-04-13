//
// Created by Dmitriy Dudurev on 12.04.2026.
//

#ifndef LAB_02_SET_HPP
#define LAB_02_SET_HPP

#include "Set.h"
#include "SetNode.hpp"
#include <ranges>
#include <iostream>

template <ContainerValue T>
Set<T>::Set()
{
    this->head = nullptr;
    this->_size = 0;
}

template <ContainerValue T>
Set<T>::Set(const Set<T> &other) : Set()
{
    for (const auto &element: other)
        add(element);
}

template <ContainerValue T>
Set<T>::Set(Set<T> &&other) : Set()
{
    this->head = std::move(other.head);
    this->_size = std::move(other._size);
    other.clear();
}

template <ContainerValue T>
template <ContainerValue U>
        requires Convertible<U, T>
Set<T>::Set(std::initializer_list<U> list) : Set()
{
    for (const auto &element: list)
        add(element);
}

template <ContainerValue T>
template <ForwardIterator I>
        requires Convertible<std::iter_value_t<I>, T>
Set<T>::Set(const I &first, const I &last) : Set()
{
    for (auto current = first; current != last; ++current)
        add(*current);
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T>::Set(const C& container) : Set()
{
    for (const auto &element: container)
        add(element);
}

template <ContainerValue T>
template <ContainerValue U>
        requires Convertible<U, T>
Set<T>::Set(size_type size, const U *array)
{
    if (array == nullptr)
        throw std::invalid_argument("Set: array pointer is null");
    if (size == 0)
        throw std::invalid_argument("Set: size is 0");

    *this = Set<T>(array, array + size);
}
// === Деструкторы ===
template <ContainerValue T>
Set<T>::~Set()
{
    if (this->head)
        this->head.reset();
}

// === Информация о множестве
template <ContainerValue T>
Set<T>::size_type Set<T>::size() const noexcept
{
    return this->_size;
}

template <ContainerValue T>
bool Set<T>::empty() const noexcept
{
    return this->_size == 0;
}

// === Итераторы ===
template <ContainerValue T>
Set<T>::const_iterator Set<T>::begin() const noexcept
{
    return const_iterator(this->head);
}

template <ContainerValue T>
Set<T>::const_iterator Set<T>::end() const noexcept
{
    return const_iterator();
}

// === Операции над множеством ===
// Очиcтка
template <ContainerValue T>
void Set<T>::clear()
{
    this->head.reset();
    this->_size = 0;
}

// Проверка вхождения в множество
template <ContainerValue T>
template <ContainerValue U>
    requires Convertible<U, T>
bool Set<T>::contains(const U &value) const
{
    return std::ranges::any_of(*this, [value](const auto& v) { return v == value; });
}

template <ContainerValue T>
template <ContainerValue U>
        requires Convertible<U, T>
void Set<T>::add(const U &value)
{
    if (!contains(value))
    {
        try
        {
            auto old_head = this->head;
            this->head = std::make_shared<Node>(value);
            this->head->set_next(old_head);
            ++this->_size;
        }
        catch (const std::bad_alloc &ex)
        {
            throw;
        }
    }
}

template <ContainerValue T>
template <Container C>
        requires Convertible<typename C::value_type, T>
void Set<T>::add(const C &container)
{
    for (const auto& element: container)
        add(element);
}

// Удаление
template <ContainerValue T>
template <ContainerValue U>
        requires Equatable<T, U>
void Set<T>::erase(const U &value)
{
    if (this->head != nullptr && this->head->get_value() == value)
    {
        this->head = this->head->get_next().lock();
        --this->_size;
    }

    for (auto cur = this->head; cur != nullptr && cur->get_next().lock() != nullptr; cur = cur->get_next().lock())
    {
        if (cur->get_next().lock()->get_value() == value)
        {
            auto next = cur->get_next().lock()->get_next().lock();
            cur->set_next(next);
            --this->_size;
        }
    }
}

template <ContainerValue T>
template <Container C>
        requires Equatable<typename C::value_type, T>
void Set<T>::erase(const C &container)
{
    for (const auto& element: container)
        erase(element);
}

// Пересечение
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::intersect(const C &container) const
{
    Set<T> intersect_set;
    for (const auto& element: container)
        if (contains(element))
            intersect_set.add(element);

    return intersect_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::intersect_update(const C &container)
{
    Set<T> intersect_set;
    for (const auto& element : container)
        if (contains(element))
            intersect_set.add(element);

    *this = intersect_set;
    return *this;
}


// Объединение
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::unite(const C &container) const
{
    Set<T> unite_set(*this);
    for (const auto& element: container)
        unite_set.add(element);

    return unite_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::unite_update(const C &container)
{
    Set<T> unite_set(*this);
    for (const auto& element: container)
        unite_set.add(element);

    *this = unite_set;
    return *this;
}

// Разность
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::difference(const C &container) const
{
    Set<T> diff_set(*this);
    diff_set.erase(container);
    return diff_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::difference_update(const C &container)
{
    erase(container);
    return *this;
}

// Симметрическая разность
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::symmetric_difference(const C &container) const
{
    Set<T> sym_diff_set(*this);
    sym_diff_set.symmetric_difference_update(container);
    return sym_diff_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::symmetric_difference_update(const C &container)
{
    Set<T> other_diff = Set<T>(container).difference(*this);
    difference_update(container);
    unite_update(other_diff);
    return *this;
}

// === Операторы ===
//  Присваивание
template <ContainerValue T>
Set<T> &Set<T>::operator=(const Set<T> &other)
{
    clear();
    for (const auto& element: other)
        add(element);

    return *this;
}
template <ContainerValue T>
template <ContainerValue U>
    requires Convertible<U, T>
Set<T> &Set<T>::operator=(const Set<U> &other)
{
    clear();
    for (const auto& element: other)
        add(element);

    return *this;
}

template <ContainerValue T>
Set<T> &Set<T>::operator=(Set<T> &&other)
{
    clear();
    this->head = std::move(other.head);
    this->_size = std::move(other._size);
    return *this;
}

template <ContainerValue T>
template <ContainerValue U>
    requires Convertible<U, T>
Set<T> &Set<T>::operator=(std::initializer_list<U> list)
{
    *this = Set<T>(list);
    return *this;
}

template <ContainerValue T>
template <Container C>
        requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::operator=(const C &container)
{
    *this = Set<T>(container);
    return *this;
}

// Объединение
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::operator+(const C &container) const
{
    return *this | container;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::operator+=(const C &container)
{
    *this |= container;
    return *this;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::operator|(const C &container) const
{
    Set<T> unite_set(*this);
    unite_set |= container;
    return unite_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::operator|=(const C &container)
{
    unite_update(container);
    return *this;
}

// Пересечение
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::operator&(const C &container) const
{
    Set<T> intersect_set(*this);
    intersect_set &= container;
    return intersect_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::operator&=(const C &container)
{
    intersect_update(container);
    return *this;
}

// Разность
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::operator-(const C &container) const
{
    Set<T> diff_set(*this);
    diff_set -= container;
    return diff_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::operator-=(const C &container)
{
    difference_update(container);
    return *this;
}

// Симметрическая разность
template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> Set<T>::operator^(const C &container) const
{
    Set<T> sym_diff_set(*this);
    sym_diff_set ^= container;
    return sym_diff_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertible<typename C::value_type, T>
Set<T> &Set<T>::operator^=(const C &container)
{
    symmetric_difference_update(container);
    return *this;
}

template <ContainerValue T>
Set<T>::operator bool() const noexcept
{
    return this->_size != 0;
}

template <ContainerValue T>
std::ostream &operator<<(std::ostream &os, const Set<T> &set)
{
    os << "{ ";

    auto range = set | std::views::transform([](const auto &e) {
        return std::to_string(e) + ", ";
    });

    std::ranges::copy(range, std::ostream_iterator<std::string>(os));

    os << "}";
    return os;
}

#endif //LAB_02_SET_HPP