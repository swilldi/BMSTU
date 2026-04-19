//
// Created by Dmitriy Dudurev on 12.04.2026.
//

#ifndef LAB_02_SET_HPP
#define LAB_02_SET_HPP

#include "Set.h"
#include "SetNode.hpp"
#include <ranges>
#include <iostream>
#include <source_location>
#include "Exceptions.h"

template <ContainerValue T>
Set<T>::Set()
{
    // std::cout << "1" << std::endl;
    this->head = nullptr;
    this->tail = nullptr;
    this->_size = 0;
}

template <ContainerValue T>
Set<T>::Set(const Set<T> &other) : Set()
{
    for (const auto &element : other)
        add(element);
}

template <ContainerValue T>
Set<T> &Set<T>::operator=(const Set<T> &other)
{
    if (this != &other)
    {
        clear();
        for (const auto &element : other)
            add(element);
    }

    return *this;
}

template <ContainerValue T>
template <ConvertableContainerValue<T> U>

Set<T>::Set(const Set<U> &other) : Set()
{
    for (const auto &element : other)
        add(element);
}

template <ContainerValue T>
template <ConvertableContainerValue<T> U>
Set<T> &Set<T>::operator=(const Set<U> &other)
{
    clear();
    for (const auto &element : other)
        add(element);

    return *this;
}

template <ContainerValue T>
Set<T>::Set(Set<T> &&other) noexcept(std::is_nothrow_move_constructible_v<T>) : Set()
{
    this->head = std::move(other.head);
    this->tail = std::move(other.tail);
    this->_size = std::move(other._size);
    other._size = 0;
}

template <ContainerValue T>
Set<T> &Set<T>::operator=(Set<T> &&other) noexcept(std::is_nothrow_move_constructible_v<T>)
{
    this->head = std::move(other.head);
    this->_size = std::move(other._size);
    this->tail = std::move(other.tail);

    other._size = 0;
    return *this;
}

template <ContainerValue T>
template <ConvertableContainerValue<T> U>
Set<T>::Set(std::initializer_list<U> list) : Set()
{
    for (const auto &element : list)
        add(element);
}

template <ContainerValue T>
template <ConvertableContainerValue<T> U>
Set<T> &Set<T>::operator=(std::initializer_list<U> list)
{
    *this = Set<T>(list);
    return *this;
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T>::Set(const C &container) : Set()
{
    for (const auto &element : container)
        add(element);
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::operator=(const C &container)
{
    *this = Set<T>(container);
    return *this;
}

template <ContainerValue T>
template <ConvertibleRange<T> R>
Set<T>::Set(const R &range) : Set()
{
    for (const auto &element : range)
        add(element);
}

template <ContainerValue T>
template <ConvertibleRange<T> R>
Set<T> &Set<T>::operator=(const R &range)
{
    *this = Set(range);
    return *this;
}

template <ContainerValue T>
template <ConvertableForwardIterator<T> I, Sentinel<I> S>
Set<T>::Set(const I &first, const S &last) : Set()
{
    for (auto current = first; current != last; ++current)
        add(*current);
}

template <ContainerValue T>
template <ConvertableContainerValue<T> U>
Set<T>::Set(size_type size, const U *array)
{
    if (array == nullptr)
        throw SetArrayNullptrException(std::source_location::current());
    if (size == 0)
        throw SetArrayZeroSizeException(std::source_location::current());

    *this = Set<T>(array, array + size);
}

// === Деструктор ===
template <ContainerValue T>
Set<T>::~Set()
{
    if (this->head)
        this->head.reset();
    if (this->tail)
        this->tail.reset();
}

// === Информация о множестве ===
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
Set<T>::iterator Set<T>::begin() const noexcept
{
    return iterator(this->head);
}

template <ContainerValue T>
Set<T>::iterator Set<T>::end() const noexcept
{
    return iterator();
}

template <ContainerValue T>
Set<T>::const_iterator Set<T>::cbegin() const noexcept
{
    return const_iterator(this->head);
}

template <ContainerValue T>
Set<T>::const_iterator Set<T>::cend() const noexcept
{
    return this->tail ?  const_iterator(tail->get_next()) : const_iterator();
}

// === Операции над множеством ===
// Очиcтка
template <ContainerValue T>
void Set<T>::clear() noexcept
{
    this->head.reset();
    this->tail.reset();
    this->_size = 0;
}

// Проверка вхождения в множество
template <ContainerValue T>
template <ConvertableContainerValue<T> U>
bool Set<T>::contains(const U &value) const noexcept
{
    return std::ranges::any_of(*this, [&value](const auto &v) { return v == value; });
}

template <ContainerValue T>
bool Set<T>::add(std::shared_ptr<Node> &node)
{
    bool added = false;
    if (!contains(node->get_value()))
    {
        if (empty())
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->set_next(node);
            tail = node;
        }

        ++_size;
        added = true;
    }
    return added;
}

template <ContainerValue T>
template <ConvertableContainerValue<T> U>
bool Set<T>::add(const U &value)
{
    bool added = false;
    try
    {
        std::shared_ptr<Node> node = std::make_shared<Node>(value);
        added = add(node);
    }
    catch (const std::bad_alloc &ex)
    {
        throw SetMemoryAllocException(std::source_location::current());
    }

    return added;
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
bool Set<T>::add(const C &container)
{
    bool added = false;
    for (const auto &element : container)
    {
        if (add(element))
            added = true;
    }

    return added;
}

// Удаление
template <ContainerValue T>
template <EquatableContainerValue<T> U>
bool Set<T>::erase(const U &value) noexcept
{
    bool element_found = false;

    if (this->head != nullptr && this->head->get_value() == value)
    {
        this->head = this->head->get_next().lock();
        if (this->head == nullptr)  // список стал пустым
            this->tail = nullptr;   // ← обновить tail
        --this->_size;
        element_found = true;
    }

    for (auto cur = this->head; !element_found && cur != nullptr; cur = cur->get_next().lock())
    {
        auto next = cur->get_next().lock();
        if (next == nullptr) break;

        if (next->get_value() == value)
        {
            auto next_next = next->get_next().lock();
            cur->set_next(next_next);
            if (next_next == nullptr)
                this->tail = cur;
            --this->_size;
            element_found = true;
        }
    }

    return element_found;
}

template <ContainerValue T>
template <EquatableContainer<T> C>
bool Set<T>::erase(const C &container) noexcept
{
    bool erased = false;
    for (const auto &element : container)
    {
        if (erase(element))
            erased = true;
    }

    return erased;
}

// Пересечение
template <ContainerValue T>
template <EquatableContainer<T> C>
Set<T> &Set<T>::intersect_update(const C &container) noexcept
{
    bool found = false;
    for (const auto &element_this : *this)
    {
        found = false;
        for (const auto &element_container : container)
        {
            if (element_container == element_container)
                found = true;
        }

        if (!found)
            this->erase(element_this);
    }
    return *this;
}

template <ContainerValue T>
template <EquatableContainer<T> C>
Set<T> &Set<T>::operator&=(const C &container) noexcept
{
    intersect_update(container);
    return *this;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::intersect(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> intersect_set(*this);
    intersect_set.intersect_update(container);
    return intersect_set;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator&(const C &container) const
{
    return intersect(container);
}

// Объединение
template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::unite_update(const C &container)
{
    for (const auto &element : container)
        add(element);

    return *this;
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::operator|=(const C &container)
{
    unite_update(container);
    return *this;
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::operator+=(const C &container)
{
    *this |= container;
    return *this;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::unite(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> unite_set(*this);
    unite_set.unite_update(container);
    return unite_set;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator|(const C &container) const
{
    return unite(container);
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator+(const C &container) const
{
    return *this | container;
}


// Разность
template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::difference_update(const C &container)
{
    erase(container);
    return *this;
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::operator-=(const C &container)
{
    difference_update(container);
    return *this;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::difference(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> diff_set(*this);
    diff_set.difference_update(container);
    return diff_set;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator-(const C &container) const
{
    return difference(container);
}


// Симметрическая разность
template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::symmetric_difference_update(const C &container)
{
    Set<T> other_diff = Set<T>(container).difference(*this);
    difference_update(container);
    unite_update(other_diff);
    return *this;
}

template <ContainerValue T>
template <ConvertableContainer<T> C>
Set<T> &Set<T>::operator^=(const C &container)
{
    symmetric_difference_update(container);
    return *this;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::symmetric_difference(const C &container) const
{
    Set<std::common_type_t<T, typename C::value_type>> sym_diff_set(*this);
    sym_diff_set.symmetric_difference_update(container);
    return sym_diff_set;
}

template <ContainerValue T>
template <CommonContainer<T> C>
Set<std::common_type_t<T, typename C::value_type>> Set<T>::operator^(const C &container) const
{
    return symmetric_difference(container);
}

// Отношения множеств
template <ContainerValue T>
template <EquatableContainerValue<T> U>
bool Set<T>::subset_of(const Set<U> &other) const noexcept
{
    return std::ranges::all_of(*this, [&other](const auto& e) { return other.contains(e); });
}

template <ContainerValue T>
template <EquatableContainerValue<T> U>
bool Set<T>::superset_of(const Set<U> &other) const noexcept
{
    return other.subset_of(*this);
}

template <ContainerValue T>
template <EquatableContainerValue<T> U>
bool Set<T>::equal(const Set<U> &other) const noexcept
{
    return this->_size == other.size() && this->subset_of(other);
}

template <ContainerValue T>
template <EquatableContainerValue<T> U>
bool Set<T>::operator==(const Set<U> &other) const
{
    return this->equal(other);
}

template <ContainerValue T>
template <EquatableContainerValue<T> U>
bool Set<T>::not_equal(const Set<U> &other) const noexcept
{
    return !this->equal(other);
}

template <ContainerValue T>
template <EquatableContainerValue<T> U>
std::partial_ordering Set<T>::operator<=>(const Set<U> &other) const noexcept
{
    if (equal(other))
        return std::partial_ordering::equivalent;
    if (subset_of(other))
        return std::partial_ordering::less;
    if (superset_of(other))
        return std::partial_ordering::greater;

    return std::partial_ordering::unordered;

}

// === Операторы ===
template <ContainerValue T>
Set<T>::operator bool() const noexcept
{
    return this->_size != 0;
}

template <ContainerValue T>
std::ostream &operator<<(std::ostream &os, const Set<T> &set)
{
    os << "{ ";

    for (const auto &element : set)
        os << element << ", ";

    os << "}";
    os << " (" << set.size() << ")";

    return os;
}

#endif //LAB_02_SET_HPP
