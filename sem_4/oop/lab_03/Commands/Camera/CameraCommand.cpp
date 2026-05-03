//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "CameraCommand.h"

#include "Managers/ManagerSolution.h"

// === Добавление камеры ===
AddCameraCommand::AddCameraCommand(const CameraID &id) :
    _action(&CameraManager::add_camera), _id(id), _camera_manager(ManagerSolution::get_camera_manager()) { }

void AddCameraCommand::execute()
{
    (*_camera_manager.*_action)(_id);
}


// === Удаление камеры ===
RemoveCameraCommand::RemoveCameraCommand(size_t id) :
    _action(&CameraManager::remove_camera), _id(id), _camera_manager(ManagerSolution::get_camera_manager()) { }

void RemoveCameraCommand::execute()
{
    (*_camera_manager.*_action)(_id);
}


// === Выбор камеры ===
SetCameraCommand::SetCameraCommand(size_t id) :
    _action(&CameraManager::set_active_camera), _id(id),
    _camera_manager(ManagerSolution::get_camera_manager()) { }

void SetCameraCommand::execute()
{
    (*_camera_manager.*_action)(_id);
}


// === Перемещение камеры ===
MoveCameraCommand::MoveCameraCommand(size_t id, const MoveData &data) :
    _action(&TransformManager::move_object), _id(id), _data(data),
    _transform_manager(ManagerSolution::get_transform_manager()) { }

void MoveCameraCommand::execute()
{
    (*_transform_manager.*_action)(_id, _data);
}


// === Вращение камеры ===
RotateCameraCommand::RotateCameraCommand(size_t id, const RotateData &data) :
    _action(&TransformManager::rotate_object), _id(id), _data(data),
    _transform_manager(ManagerSolution::get_transform_manager()) { }

void RotateCameraCommand::execute()
{
    (*_transform_manager.*_action)(_id, _data);
}
