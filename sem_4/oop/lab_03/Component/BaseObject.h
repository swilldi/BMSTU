//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_BASEOBJECT_H
#define LAB_03_BASEOBJECT_H

#include <map>
#include <memory>
#include <cstddef>

#include "Component/SceneObject/Model/Point/Point.h"
#include "Visitor/BaseVisitor.h"

class BaseObject;
using mapObjects = std::map<size_t, std::shared_ptr<BaseObject>>;

class BaseObject
{
public:
    using iterator = mapObjects::iterator;
    using const_iterator = mapObjects::const_iterator;

    BaseObject() = default;
    virtual ~BaseObject() = default;

    virtual iterator begin();
    virtual iterator end();

    virtual const_iterator begin() const;
    virtual const_iterator end() const;

    virtual std::shared_ptr<BaseObject> get_object(const size_t id) const;
    virtual void add(std::shared_ptr<BaseObject> object);
    virtual void remove(size_t id) noexcept;

    virtual void accept(std::shared_ptr<BaseVisitor> visitor) = 0;

    virtual Point get_center() const noexcept;
    virtual bool is_composite() const noexcept = 0;
    virtual bool is_visible() const noexcept = 0;
};

#endif //LAB_03_BASEOBJECT_H