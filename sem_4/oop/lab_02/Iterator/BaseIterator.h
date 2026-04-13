//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_BASEITERATOR_H
#define LAB_02_BASEITERATOR_H

#include "Concepts.h"
#include <memory>

// class Set;

template <CopyMoveAssingable T>
class BaseIterator {
public:
    using value_type = T;
    using reference = T&;
    using pointer = std::shared_ptr<T>;
    using difference_type = std::ptrdiff_t;

    BaseIterator() = default;
    virtual ~BaseIterator() = 0;

// protected:
//     std::weak_ptr<typename Set<T>::Node> current{};
};

#endif //LAB_02_BASEITERATOR_H