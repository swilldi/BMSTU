//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "SceneManager.h"

#include "Component/Composite/Composite.h"

SceneManager::SceneManager() : _scene(Scene::get_scene()) {}

std::shared_ptr<BaseObject> SceneManager::get_object(size_t id)
{
    return _scene->get_component(id);
}

void SceneManager::add_object(std::shared_ptr<BaseObject> object)
{
    _scene->add_component(object);
}

void SceneManager::remove_object(size_t id)
{
    _scene->remove_component(id);
}

void SceneManager::get_center(size_t id, Point &center) const
{
    auto object = _scene->get_component(id);
    center = object->get_center();
}

void SceneManager::compose(std::vector<size_t> ids)
{
    auto composite = std::make_shared<Composite>();

    for (const size_t &id : ids)
        composite->add(_scene->get_component(id));

    _scene->add_component(composite);
}

void SceneManager::accept(std::shared_ptr<BaseVisitor> visitor)
{
    _scene->accept(visitor);
}
