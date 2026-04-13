//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_CONSTITERATOR_HPP
#define LAB_02_CONSTITERATOR_HPP

#include "SetConstIterator.h"

// === Конструкторы ===
template <ContainerValue T>
ConstIterator<T>::ConstIterator()
{
    this->current.lock() = nullptr;
}

template <ContainerValue T>
explicit ConstIterator<T>::ConstIterator(const std::shared_ptr<typename Set<T>::Node> &node)
{
    this->current = node;
}

template <ContainerValue T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &other)
{
    other.checkExpired();
    this->current.lock() = other.current.lock();
}

// === Операторы ===
template <ContainerValue T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &other) const noexcept
{
    return this->current.lock() == other.current.lock();
}

template <ContainerValue T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &other) const noexcept
{
    return this->current.lock() != other.current.lock();
}

template <ContainerValue T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &other) noexcept
{
    this->current.lock() = other.current;
    return *this;
}

template <ContainerValue T>
ConstIterator<T> &ConstIterator<T>::operator=(ConstIterator<T> &&other) noexcept
{
    this->current.lock() = std::move(other.current.lock());
    return *this;
}

template <ContainerValue T>
const T &ConstIterator<T>::operator*() const
{
    this->checkExpired();
    return getCurrent().value();
}

template <ContainerValue T>
const std::shared_ptr<T> ConstIterator<T>::operator->() const
{
    this->checkExpired();
    return this->current.lock()->get();
}

template <ContainerValue T>
ConstIterator<T> &ConstIterator<T>::operator++() const noexcept
{
    this->next();
    return *this;
}

template <ContainerValue T>
ConstIterator<T> ConstIterator<T>::operator++(int) const noexcept
{
    auto current = *this;
    this->next();
    return current;
}

template <ContainerValue T>
explicit ConstIterator<T>::operator bool() const noexcept
{
    return !this->current.expired() && this->current.lock() != nullptr;
}

// === Изменение итератора ===
template <ContainerValue T>
void ConstIterator<T>::next() noexcept
{
    this->checkExpired();
    this->current = this->getCurrent().next();
}

// === Проверка итератора ===
template <ContainerValue T>
void ConstIterator<T>::checkExpired() const
{
    // if (this->current.expired())
    //     throw // Кидать ошибку
}

template <ContainerValue T>
typename Set<T>::Node &ConstIterator<T>::getCurrent() const
{
    this->checkExpired();
    return *this->current.lock();
}

#endif //LAB_02_CONSTITERATOR_HPP
