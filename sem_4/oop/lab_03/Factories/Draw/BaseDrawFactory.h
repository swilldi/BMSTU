//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEDRAWFACTORY_H
#define LAB_03_BASEDRAWFACTORY_H
#include "Products/BaseDrawer.h"

#include <memory>

class BaseDrawFactory
{
public:
    BaseDrawFactory() = default;
    virtual ~BaseDrawFactory() = default;

    virtual std::unique_ptr<BaseDrawer> create_drawer() = 0;
};

#endif //LAB_03_BASEDRAWFACTORY_H