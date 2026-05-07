//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_BASEDIRECTOR_H
#define LAB_03_BASEDIRECTOR_H
#include "Builders/BaseBuilder.h"
#include "Component/BaseObject.h"
#include "../Component/SceneObject/Model/Implementor/BaseModelImpl.h"

#include <memory>

template <typename Product>
class BaseDirector
{
public:
    BaseDirector() = default;
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseObject> create() const = 0;

protected:
    std::shared_ptr<BaseBuilder<Product>> _builder;
};

using BaseModelDirector = BaseDirector<BaseModelImpl>;

#endif //LAB_03_BASEDIRECTOR_H
