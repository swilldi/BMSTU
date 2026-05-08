//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "CameraManager.h"

#include "Exceptions/Manager/Camera/CameraManagerException.h"
#include "Factories/Camera/CameraFactory.h"
#include "Managers/ManagerSolution.h"

void CameraManager::set_active_camera(size_t id)
{
    auto scene_manager = ManagerSolution::get_scene_manager();
    auto camera_obj = scene_manager->get_object(id);
    auto camera = std::dynamic_pointer_cast<BaseCamera>(camera_obj);

    if (!camera)
        throw CameraManagerInvalidID();

    _active_camera = camera;
    _active_camera_id = id;

    auto draw_manager = ManagerSolution::get_draw_manager();
    draw_manager->draw();
}

std::shared_ptr<BaseCamera> CameraManager::get_active_camera() const noexcept
{
    return _active_camera;
}

void CameraManager::add_camera(const CameraID &id)
{
    CameraFactory factory;
    auto camera = factory.create(id);

    auto scene_manager = ManagerSolution::get_scene_manager();
    scene_manager->add_object(camera);
}

void CameraManager::remove_camera(size_t id)
{
    auto scene_manager = ManagerSolution::get_scene_manager();
    scene_manager->remove_object(id);
}
