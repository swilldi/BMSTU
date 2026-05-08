//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "Scene.h"

#include "Exceptions/Scene/SceneException.h"

Scene::Scene() : _object_count(0) {}

Scene::iterator Scene::begin()
{
    return _objects.begin();
}

Scene::iterator Scene::end()
{
    return _objects.end();
}

Scene::const_iterator Scene::begin() const
{
    return _objects.begin();
}

Scene::const_iterator Scene::end() const
{
    return _objects.end();
}

Scene::ObjectId Scene::add_component(ObjectPtr object)
{
    _objects.insert(MapObjects::value_type(_object_count++, object));
    return _object_count - 1;
}

Scene::iterator Scene::get_component(ObjectId id)
{
    auto it = _objects.find(id);
    if (it == _objects.end())
        throw SceneInvalidObjectID();

    return it;
}

Scene::const_iterator Scene::get_component(ObjectId id) const
{
    auto it = _objects.find(id);
    if (it == _objects.end())
        throw SceneInvalidObjectID();

    return it;
}

void Scene::accept(std::shared_ptr<BaseVisitor> visitor)
{
    for (auto &[id, component] : _objects)
        component->accept(visitor);
}

std::shared_ptr<Scene> Scene::get_scene()
{
    class Proxy : public Scene { };

    static std::shared_ptr<Scene> scene = std::make_shared<Proxy>();
    return scene;
}

void Scene::remove_component(ObjectId id)
{
    _objects.erase(get_component(id));
}
