//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "Composite.h"

#include "Exceptions/Composite/CompositeException.h"

Composite::Composite(const MapObjects &objects): _objects(objects) { }

BaseObject::iterator Composite::begin()
{
    return _objects.begin();
}

BaseObject::iterator Composite::end()
{
    return _objects.end();
}

BaseObject::const_iterator Composite::begin() const
{
    return _objects.begin();
}

BaseObject::const_iterator Composite::end() const
{
    return _objects.end();
}

// TODO
Point Composite::get_center() const noexcept
{
    // Point center = { 0, 0, 0};
    // for (conat auto &point )
}

bool Composite::is_composite() const noexcept
{
    return true;
}

bool Composite::is_visible() const noexcept
{
    return false;
}

void Composite::add(std::shared_ptr<BaseObject> object)
{
    _objects[_count] = object;
    ++_count;
}

void Composite::remove(size_t id) noexcept
{
    _objects.erase(id);
}


std::shared_ptr<BaseObject> Composite::get_object(const size_t id) const
{
    std::shared_ptr<BaseObject> object;
    try
    {
        object = _objects.at(id);
    }
    catch (const std::out_of_range &e)
    {
        // TODO
        throw CompositeIndexOutOfRange();
    }

    return object;
}

// TODO
void Composite::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &[id, component]: _objects)
        component->accept(visitor);
}


