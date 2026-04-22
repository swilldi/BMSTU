//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_CONSTITERATOR_H
#define LAB_02_CONSTITERATOR_H

#include "BaseIterator.h"
#include "Concepts.h"
#include <iterator>
#include <memory>

template<ContainerValue T>
class Set;

template<ContainerValue T>
class SetConstIterator final : public BaseIterator<T> {
public:
    using typename BaseIterator<T>::value_type;
    using typename BaseIterator<T>::reference;
    using typename BaseIterator<T>::pointer;
    using typename BaseIterator<T>::difference_type;
    using iterator_category = std::forward_iterator_tag;

    // === Конструкторы ===
    SetConstIterator() noexcept = default;
    SetConstIterator(const SetConstIterator<T>& other);
    explicit SetConstIterator(const std::shared_ptr<typename Set<T>::Node>& node) noexcept;

    // === Деструктор ===
    ~SetConstIterator() override = default;

    // === Операторы ===
    SetConstIterator<T> &operator=(const SetConstIterator<T>& other);
    SetConstIterator<T> &operator=(SetConstIterator<T> &&other) noexcept;

    reference operator*() const;
    pointer operator->() const;

    SetConstIterator<T> &operator++() noexcept;
    SetConstIterator<T> operator++(int) noexcept;

    bool operator==(const SetConstIterator<T> &other) const noexcept;

    explicit operator bool() const noexcept;

    void next() noexcept;

private:
    void check_expired() const;
    std::weak_ptr<typename Set<T>::Node> value;
};

#include "SetConstIterator.hpp"

#endif //LAB_02_CONSTITERATOR_H
