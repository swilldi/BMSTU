//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_CAMERACOMMAND_H
#define LAB_03_CAMERACOMMAND_H
#include "Commands/BaseCommand.h"
#include "Managers/Camera/CameraManager.h"
#include "ID/ID.h"
#include "Managers/Transform/TransformManager.h"
#include "Transform/Data/Move/MoveData.h"

// === Базовый класс ===
class CameraCommand : public BaseCommand
{
public:
    CameraCommand() = default;
    virtual ~CameraCommand() = default;
};


// === Добавление камеры ===
class AddCameraCommand final : public CameraCommand
{
public:
    AddCameraCommand(const CameraID &id);
    virtual ~AddCameraCommand() override = default;

    void execute() override;

private:
    using Action = void (CameraManager::*)(const CameraID &);

    Action _action;
    CameraID _id;
    std::shared_ptr<CameraManager> _camera_manager;
};


// === Удаление камеры ===
class RemoveCameraCommand : public CameraCommand
{
public:
    RemoveCameraCommand(size_t id);
    virtual ~RemoveCameraCommand() override = default;

    void execute() override;

private:
    using Action = void (CameraManager::*)(size_t);

    Action _action;
    size_t _id;
    std::shared_ptr<CameraManager> _camera_manager;

};


// === Выбор камеры ===
class SetCameraCommand : public CameraCommand
{
public:
    SetCameraCommand(size_t id);
    virtual ~SetCameraCommand() override = default;

    void execute() override;

private:
    using Action = void (CameraManager::*)(size_t);

    Action _action;
    size_t _id;
    std::shared_ptr<CameraManager> _camera_manager;
};


// === Перемещение камеры ===
class MoveCameraCommand : public CameraCommand
{
public:
    MoveCameraCommand(size_t id, const MoveData &data);
    virtual ~MoveCameraCommand() override = default;

    void execute() override;

private:
    using Action = void (TransformManager::*)(size_t, const MoveData &);

    Action _action;
    size_t _id;
    MoveData _data;
    std::shared_ptr<TransformManager> _transform_manager;
};


// === Вращение камеры ===
class RotateCameraCommand : public CameraCommand
{
public:
    RotateCameraCommand(size_t id, const RotateData &data);
    virtual ~RotateCameraCommand() override = default;

    void execute() override;

private:
    using Action = void (TransformManager::*)(size_t, const RotateData &);

    Action _action;
    size_t _id;
    RotateData _data;
    std::shared_ptr<TransformManager> _transform_manager;
};


#endif //LAB_03_CAMERACOMMAND_H