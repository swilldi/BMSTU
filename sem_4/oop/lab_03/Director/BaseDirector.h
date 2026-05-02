//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEDIRECTOR_H
#define LAB_03_BASEDIRECTOR_H
#include "Builders/BaseBuilder.h"

#include <memory>

class BaseDirector
{
public:
    BaseDirector() = default;
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseObject> create() const = 0;

protected:
    std::shared_ptr<BaseBuilder> _builder;
};

#endif //LAB_03_BASEDIRECTOR_H