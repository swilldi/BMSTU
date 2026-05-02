//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "BoneDirector.h"

BoneDirector::BoneDirector(std::shared_ptr<BaseBuilder> builder)
{
    _builder = builder;
}

std::shared_ptr<BaseObject> BoneDirector::create() const
{
    return _builder->get_product();
}
