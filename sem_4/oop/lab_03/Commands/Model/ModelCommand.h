//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#ifndef LAB_03_MODELCOMMAND_H
#define LAB_03_MODELCOMMAND_H
#include "Commands/BaseCommand.h"
#include "Component/BaseObject.h"
#include "Managers/Scene/SceneManager.h"
#include "Managers/Transform/TransformManager.h"
#include "Transform/Data/Move/MoveData.h"

class ModelCommand : public BaseCommand
{
public:
    ModelCommand() = default;
    virtual ~ModelCommand() = default;
};


// === Добавление модели ===
class AddModelCommand : public BaseCommand
{
public:
    AddModelCommand(std::shared_ptr<BaseObject> model);
    virtual ~AddModelCommand() override = default;

    void execute() override;

private:
    using Action = void (SceneManager::*)(std::shared_ptr<BaseObject>);

    Action _action;
    std::shared_ptr<BaseObject> _model;
    std::shared_ptr<SceneManager> _scene_manager;
};


// === Удаление модели ===
class RemoveModelCommand : public BaseCommand
{
public:
    RemoveModelCommand(size_t id);
    virtual ~RemoveModelCommand() override = default;

    void execute() override;

private:
    using Action = void (SceneManager::*)(size_t);

    Action _action;
    size_t _id;
    std::shared_ptr<SceneManager> _scene_manager;
};


// === Перемещение модели ===
class MoveModelCommand : public BaseCommand
{
public:
    MoveModelCommand(size_t id, const MoveData &data);
    virtual ~MoveModelCommand() override = default;

    void execute() override;

private:
    using Action = void (TransformManager::*)(size_t, const MoveData &);

    Action _action;
    size_t _id;
    MoveData _data;
    std::shared_ptr<TransformManager> _transform_manager;
};


// === Вращение модели ===
class RotateModelCommand : public BaseCommand
{
public:
    RotateModelCommand(size_t id, const RotateData &data);
    virtual ~RotateModelCommand() override = default;

    void execute() override;

private:
    using Action = void (TransformManager::*)(size_t, const RotateData &);

    Action _action;
    size_t _id;
    RotateData _data;
    std::shared_ptr<TransformManager> _transform_manager;
};


// === Масштабирование модели ===
class ScaleModelCommand : public BaseCommand
{
public:
    ScaleModelCommand(size_t id, const ScaleData &data);
    virtual ~ScaleModelCommand() override = default;

    void execute() override;

private:
    using Action = void (TransformManager::*)(size_t, const ScaleData &);

    Action _action;
    size_t _id;
    ScaleData _data;
    std::shared_ptr<TransformManager> _transform_manager;
};


// === Композиция моделей ===
class ComposeCommand : public ModelCommand
{
public:
    ComposeCommand(std::vector<size_t> ids);
    virtual ~ComposeCommand() override = default;

    void execute() override;

private:
    using Action = void (SceneManager::*)(std::vector<size_t>);

    Action _action;
    std::vector<size_t> _ids;
    std::shared_ptr<SceneManager> _scene_manager;
};


// === Центр модели ===
class GetCenterModelCommand : public ModelCommand
{
public:
    GetCenterModelCommand(size_t id, Point &center);
    virtual ~GetCenterModelCommand() override = default;

    void execute() override;

private:
    using Action = void (SceneManager::*)(size_t, Point &) const;

    Action _action;
    size_t _id;
    Point &_center;
    std::shared_ptr<SceneManager> _scene_manager;
};

#endif //LAB_03_MODELCOMMAND_H