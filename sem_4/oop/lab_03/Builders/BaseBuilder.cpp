//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BaseBuilder.h"

std::shared_ptr<BaseObject> BaseBuilder::get_product()
{
    if (!_product)
        _product = create_product();

    return _product;
}
