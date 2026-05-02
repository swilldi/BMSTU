//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_SCENEMANAGER_H
#define LAB_03_SCENEMANAGER_H
#include "Managers/BaseManager.h"
#include "Scene/Scene.h"

#include <memory>

class SceneManager : public BaseManager
{
public:
    SceneManager();
    virtual ~SceneManager() = default;

    std::shared_ptr<BaseObject> get_object(size_t id);

    void add_object(std::shared_ptr<BaseObject> object);
    void remove_object(size_t id);

    void get_center(size_t id, Point &center) const;

    void compose(std::vector<size_t> ids);
    void accept(std::shared_ptr<BaseVisitor> visitor);
private:
    std::shared_ptr<Scene> _scene;
};

#endif //LAB_03_SCENEMANAGER_H