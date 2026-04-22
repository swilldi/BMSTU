//
// Created by Dmitriy Dudurev on 11.04.2026.
//

#ifndef LAB_02_BASECONTAINER_H
#define LAB_02_BASECONTAINER_H

#include <cstddef>

class BaseSet
{
public:
    using size_type = size_t;

    BaseSet() = default;

    virtual ~BaseSet() = default;

    virtual size_type size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

protected:
    size_type _size = 0;
};

#endif //LAB_02_BASECONTAINER_H
