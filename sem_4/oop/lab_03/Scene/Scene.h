//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_SCENE_H
#define LAB_03_SCENE_H

#include "Component/BaseObject.h"

class Scene {
public:
    using iterator = MapObjects::iterator;

    Scene(const Scene &other) = delete;
    Scene(Scene &&other) = delete;

    ~Scene() = default;

    static std::shared_ptr<Scene> get_scene();

    iterator begin();
    iterator end();

    size_t add_component(std::shared_ptr<BaseObject> object);
    std::shared_ptr<BaseObject> get_component(size_t id);
    void remove_component(size_t id);

    void accept(std::shared_ptr<BaseVisitor> visitor);

private:
    size_t _object_count;
    MapObjects _objects;

    Scene() = default;
};


#endif //LAB_03_SCENE_H