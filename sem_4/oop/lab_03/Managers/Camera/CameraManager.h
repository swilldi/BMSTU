//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_CAMERAMANAGER_H
#define LAB_03_CAMERAMANAGER_H
#include "Component/SceneObject/Camera/BaseCamera.h"
#include "ID/ID.h"
#include "Managers/BaseManager.h"
#include <cstddef>
#include <memory>

class CameraManager : public BaseManager
{
public:
    CameraManager() = default;
    virtual ~CameraManager() override = default;

    void add_camera(const CameraID &id);
    void remove_camera(size_t id);

    void set_active_camera(size_t id);
    std::shared_ptr<BaseCamera> get_active_camera() const noexcept;

private:
    std::shared_ptr<BaseCamera> _active_camera;
    size_t _active_camera_id;
};

#endif //LAB_03_CAMERAMANAGER_H