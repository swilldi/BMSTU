//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEBUILDER_H
#define LAB_03_BASEBUILDER_H
#include "Component/BaseObject.h"

#include <memory>
class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    std::shared_ptr<BaseObject> get_product();

protected:
    std::shared_ptr<BaseObject> _product;
    size_t _part;

    virtual std::shared_ptr<BaseObject> create_product() = 0;
};


#endif //LAB_03_BASEBUILDER_H
