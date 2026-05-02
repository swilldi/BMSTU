//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "Scene.h"

size_t Scene::add_component(std::shared_ptr<BaseObject> object)
{
    _objects.insert(MapObjects::value_type(_object_count++, object));
    return _object_count - 1;
}

std::shared_ptr<BaseObject> Scene::get_component(size_t id)
{
    try
    {
        return _objects.at(id);
    }
    catch (const std::out_of_range &e)
    {
        throw nullptr;
    }
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
