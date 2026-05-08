//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BaseBuilder.h"

template <typename Product>
std::shared_ptr<Product> BaseBuilder<Product>::get_product()
{
    if (!_product)
        _product = create_product();

    return _product;
}
