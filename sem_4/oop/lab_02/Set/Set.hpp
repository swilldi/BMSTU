//
// Created by Dmitriy Dudurev on 12.04.2026.
//

#ifndef LAB_02_SET_HPP
#define LAB_02_SET_HPP

#include "Set.h"
#include <ranges>

template <ContainerValue T>
Set<T>::Set()
{
    head = nullptr;
    size = 0;
}

template <ContainerValue T>
Set<T>::Set(const Set<T> &other)
{
    clear();
    for (const auto &element: other)
        add(element);
}

template <ContainerValue T>
Set<T>::Set(Set<T> &&other)
{
    head = std::move(other.head);
    size = std::move(other.size);
    other.clear();
}

template <ContainerValue T>
template <ContainerValue U>
        requires Convertable<U, T>
Set<T>::Set(std::initializer_list<U> list)
{
    clear();
    for (const auto &element: list)
        add(element);
}

template <ContainerValue T>
template <ForwardIterator I>
        requires Convertable<typename I::value_type, T>
Set<T>::Set(const I &first, const I &last)
{
    clear();
    for (auto current = first; current != last; ++current)
        add(*current);
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T>::Set(const C& container)
{
    clear();
    for (const auto &element: container)
        add(element);
}

template <ContainerValue T>
template <ContainerValue U>
        requires Convertable<U, T>
Set<T>::Set(size_type size, const U *array)
{
    // if (array == nullptr)
    //     throw

    // if (size == 0)
    //     throw

    Set<T> result(array, array + size);
    return result;
}

// === Деструкторы ====
template <ContainerValue T>
Set<T>::~Set()
{
    if (head)
        head.reset();
}

// === Информация о множестве
template <ContainerValue T>
size_type Set<T>::get_size() override
{
    return size;
}

template <ContainerValue T>
bool Set<T>::empty() override
{
    return size == 0;
}

// === Итераторы ===
template <ContainerValue T>
const_iterator Set<T>::begin() const noexcept
{
    return const_iterator(head);
}

template <ContainerValue T>
const_iterator Set<T>::end() const noexcept
{
    return const_iterator();
}

// === Операции над множеством ===
// Очитка
template <ContainerValue T>
void Set<T>::clear()
{
    head.reset();
    size = 0;
}

// Проверка вхождения в множество
template <ContainerValue T>
template <ContainerValue U>
    requires Convertable<U, T>
bool Set<T>::contains(const U &value) const
{
    return std::ranges::any_of(*this, [value](const auto& v) { return v == value; });
}

template <ContainerValue T>
template <ContainerValue U>
        requires Convertable<U, T>
void Set<T>::add(const U &value)
{
    if (!contains(value))
    {
        try
        {
            auto old_head = head;
            head = std::make_shared<Node>(value);
            head->set_next(old_head);
            ++size;
        }
        catch (const std::bad_alloc &ex)
        {
            // throw
        }
    }
}

template <ContainerValue T>
template <Container C>
        requires Convertable<typename C::value_type, T>
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
    for (auto n = head; n != nullptr && n->get_next().lock() != nullptr; n = n->get_next().lock())
    {
        if (n->get_next().lock()->get_value() == value)
        {
            auto next = n->get_next().lock()->get_next().lock();
            n->set_next(next);
        }
    }
}

template <ContainerValue T>
template <Container С>
        requires Equatable<typename С::value_type, T>
void Set<T>::erase(const С &container)
{
    for (const auto& element: container)
        erase(element);
}

// Пересечение
template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::intersect(const C &container) const
{
    Set<T> intersect_set();
    for (const auto& element: container)
        if (contains(element))
            intersect_set.add(*element);

    return intersect_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
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
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::unite(const C &container) const
{
    Set<T> unite_set(*this);
    for (const auto& element: container)
        unite_set.add(element);

    return unite_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
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
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::difference(const C &container) const
{
    Set<T> diff_set(*this);
    diff_set.erase(container);
    return diff_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::difference_update(const C &container)
{
    erase(container);
    return *this;
}

// Симетрическая разность
template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::symmetric_difference(const C &container) const
{
    Set<T> sym_diff_set(*this);
    sym_diff_set.symmetric_difference_update(container);
    return sym_diff_set;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::symmetric_difference_update(const C &container)
{
    Set<T> other_diff = Set<T>(container).difference(*this);
    difference_update(container);
    union_update(other_diff);
    return *this;
}

// === Операторы ===
//  Присваивание
template <ContainerValue T>
template <ContainerValue U>
    requires Convertable<U, T>
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
    head = std::move(other.head);
    size = std::move(other.size);
    return *this;
}

template <ContainerValue T>
template <ContainerValue U>
    requires Convertable<U, T>
Set<T> &Set<T>::operator=(std::initializer_list<U> list)
{
    *this = Set<T>(list);
    return *this;
}

template <ContainerValue T>
template <Container C>
        requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::operator=(const C &container)
{
    *this = Set<T>(container);
    return *this;
}

// Объединение
template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::operator+(const C &container) const
{
    return *this | container;
}

template <ContainerValue T>
template <Container C>
        requires Convertable<typename C::value_type, T>
Set<T> Set<T>::operator+(const C &container, const Set<T>& set)
{
    return set | container;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::operator+=(const C &container)
{
    *this |= container;
    return *this;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::operator|(const C &container) const
{
    Set<T> unite_set(*this);
    unite_set |= container;
    return unite_set;
}

template <ContainerValue T, Container C>
        requires Convertable<typename C::value_type, T>
Set<T> operator|(const C &container, const Set<T>& set)
{
    return set | container;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::operator|=(const C &container)
{
    unite_update(container);
    return *this;
}

// Пересечение
template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::operator&(const C &container) const
{
    Set<T> intersect_set(*this);
    intersect_set &= container;
    return intersect_set;
}

template <ContainerValue T, Container C>
    requires Convertable<typename C::value_type, T>
Set<T> operator&(const C &container, const Set<T>& set)
{
    return set & container;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::operator&=(const C &container)
{
    intersect_update(container);
    return *this;
}

// Разность
template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::operator-(const C &container) const
{
    Set<T> diff_set(*this);
    diff_set -= container;
    return diff_set;
}

template <ContainerValue T, Container C>
    requires Convertable<typename C::value_type, T>
Set<T> operator-(const C &container, Set<T> &set)
{
    return set - container;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::operator-=(const C &container)
{
    difference_update(container);
    return *this;
}

// Симетрическая разность
template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> Set<T>::operator^(const C &container) const
{
    Set<T> sym_diff_set(*this);
    sym_diff_set ^= container;
    return sym_diff_set;
}

template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> operator^(const C &container, Set<T> &set)
{
    return set ^ container;
}

template <ContainerValue T>
template <Container C>
    requires Convertable<typename C::value_type, T>
Set<T> &Set<T>::operator^=(const C &container)
{
    symmetric_difference_update(container);
    return *this;
}

template <ContainerValue T>
Set<T>::operator bool() const noexcept
{
    return size != 0;
}

#endif //LAB_02_SET_HPP