//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEBUILDER_H
#define LAB_03_BASEBUILDER_H

#include <cstddef>
#include <memory>

template <typename Product>
class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    std::shared_ptr<Product> get_product();

protected:
    std::shared_ptr<Product> _product{ nullptr };
    size_t _part{ 0 };

    virtual std::shared_ptr<Product> create_product() = 0;
};

#include "BaseBuilder.hpp"

#endif //LAB_03_BASEBUILDER_H
