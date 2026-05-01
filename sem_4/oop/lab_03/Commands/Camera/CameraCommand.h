//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_CAMERACOMMAND_H
#define LAB_03_CAMERACOMMAND_H
#include "Commands/BaseCommand.h"

class CameraCommand : public BaseCommand
{
public:
    CameraCommand() = default;
    virtual ~CameraCommand() = default;
};

class AddCameraCommand final : public CameraCommand
{
    using Action = void (CameraManager::*)(const CameraId &);

public:
    AddCameraCommand(const CameraId &id);
    virtual ~AddCameraCommand() override = default;

    void execute() override;
private:
    Action _action;
    CameraId _id;
    std::shared_ptr<CameraManager> _camera_manager;
};

#endif //LAB_03_CAMERACOMMAND_H