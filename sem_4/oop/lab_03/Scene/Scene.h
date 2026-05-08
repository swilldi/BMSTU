//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#ifndef LAB_03_SCENE_H
#define LAB_03_SCENE_H

#include "Component/BaseObject.h"

class Scene {
public:
    using ObjectId = MapObjects::key_type;
    using ObjectPtr = MapObjects::mapped_type;
    using Size = MapObjects::size_type;
    using iterator = MapObjects::iterator;
    using const_iterator = MapObjects::const_iterator;

    Scene(const Scene &other) = delete;
    Scene(Scene &&other) = delete;

    ~Scene() = default;

    static std::shared_ptr<Scene> get_scene();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    ObjectId add_component(ObjectPtr object);
    iterator get_component(ObjectId id);
    const_iterator get_component(ObjectId id) const;
    void remove_component(ObjectId id);

    void accept(std::shared_ptr<BaseVisitor> visitor);

private:
    ObjectId _object_count;
    MapObjects _objects;

    Scene();
};


#endif //LAB_03_SCENE_H
