//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "BaseObject.h"

BaseObject::iterator BaseObject::begin()
{
    return iterator();
}

BaseObject::iterator BaseObject::end()
{
    return iterator();
}

BaseObject::const_iterator BaseObject::begin() const
{
    return const_iterator();
}

BaseObject::const_iterator BaseObject::end() const
{
    return const_iterator();
}

void BaseObject::add(std::shared_ptr<BaseObject> object) { }

void BaseObject::remove(size_t id) noexcept { }

std::shared_ptr<BaseObject> BaseObject::get_object(const size_t /*id*/) const
{
    return nullptr;
}

Point BaseObject::get_center() const noexcept
{
    return { 0, 0, 0 };
}

