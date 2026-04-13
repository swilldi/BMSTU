//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_BASECONTAINER_H
#define LAB_02_BASECONTAINER_H

#include "Concepts.h"
#include <cstddef>


template <ContainerValue T>
class BaseContainer
{
public:
    using value_type = T;
    using size_type = size_t;

    BaseContainer() = default;

    virtual ~BaseContainer() = 0;

    virtual size_type get_size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

protected:
    size_type size;
};

#endif //LAB_02_BASECONTAINER_H
