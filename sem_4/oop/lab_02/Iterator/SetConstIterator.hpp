//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_CONSTITERATOR_HPP
#define LAB_02_CONSTITERATOR_HPP

#include "SetConstIterator.h"
#include "Exceptions.h"

// === Конструкторы ===
template<ContainerValue T>
SetConstIterator<T>::SetConstIterator(const SetConstIterator<T>& other)
{
    value = other.value;
}
template<ContainerValue T>
SetConstIterator<T>::SetConstIterator(const std::shared_ptr<typename Set<T>::Node>& node) noexcept
{
    value = node;
}


// === Операторы ===
template<ContainerValue T>
SetConstIterator<T> &SetConstIterator<T>::operator=(const SetConstIterator<T>& other)
{
    value = other.value;
    return *this;
}

template<ContainerValue T>
SetConstIterator<T> &SetConstIterator<T>::operator=(SetConstIterator<T> &&other) noexcept
{
    value = std::move(other.value);
    return *this;
}

template<ContainerValue T>
SetConstIterator<T>::reference SetConstIterator<T>::operator*() const
{
    check_expired();
    return value.lock()->get_value();
}
template<ContainerValue T>
SetConstIterator<T>::pointer SetConstIterator<T>::operator->() const
{
    check_expired();
    return &value.lock()->get_value();
}

template<ContainerValue T>
SetConstIterator<T> &SetConstIterator<T>::operator++() noexcept
{
    next();
    return *this;
}
template<ContainerValue T>
SetConstIterator<T> SetConstIterator<T>::operator++(int) noexcept
{
    auto copy = *this;
    this->next();
    return copy;
}

template<ContainerValue T>
bool SetConstIterator<T>::operator==(const SetConstIterator<T> &other) const noexcept
{
    return value.lock() == other.value.lock();
}

template<ContainerValue T>
SetConstIterator<T>::operator bool() const noexcept
{
    return value.lock() != nullptr;
}

template<ContainerValue T>
void SetConstIterator<T>::check_expired() const
{
    if (value.expired())
        throw IteratorPointerExpiredException(std::source_location::current());
}

template<ContainerValue T>
void SetConstIterator<T>::next() noexcept
{
    auto node = value.lock();
    if (node)
        value = node->get_next();
}

#endif //LAB_02_CONSTITERATOR_HPP
