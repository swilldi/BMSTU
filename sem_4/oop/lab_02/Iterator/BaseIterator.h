//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_BASEITERATOR_H
#define LAB_02_BASEITERATOR_H

#include "Concepts.h"
#include <memory>

template <ContainerValue T>
class Set;

template <CopyMoveAssignable T>
class BaseIterator {
public:
    using value_type = T;
    using reference = const T&;
    using pointer = const std::shared_ptr<T>;
    using difference_type = std::ptrdiff_t;

    BaseIterator() = default;
    virtual ~BaseIterator() = 0;
};

template <CopyMoveAssignable T>
inline BaseIterator<T>::~BaseIterator() {}

#endif //LAB_02_BASEITERATOR_H