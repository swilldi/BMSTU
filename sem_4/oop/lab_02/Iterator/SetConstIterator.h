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
    using iterator_category = std::forward_iterator_tag;
    using node_type = const Set<T>::Node;

    // === Конструкторы ===
    SetConstIterator() noexcept = default;
    SetConstIterator(const SetConstIterator<T>& other) = default;
    explicit SetConstIterator(const std::shared_ptr<node_type>& pnode);

    // === Деструктор ===
    ~SetConstIterator() override = default;

    // === Операторы ===
    SetConstIterator& operator=(const SetConstIterator& other);
    SetConstIterator &operator=(SetConstIterator &&other);

    const T& operator*() const;
    const T* operator->() const;

    SetConstIterator &operator++();
    SetConstIterator operator++(int);

    bool operator==(const SetConstIterator &other) const;
    bool operator!=(const SetConstIterator &other) const;

    explicit operator bool() const noexcept;

private:
    std::weak_ptr<node_type> value;
};

#include "SetConstIterator.hpp"

#endif //LAB_02_CONSTITERATOR_H
