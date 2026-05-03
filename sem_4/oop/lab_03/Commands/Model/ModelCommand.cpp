//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "ModelCommand.h"

#include "Managers/ManagerSolution.h"
// === Добавление модели ===
AddModelCommand::AddModelCommand(std::shared_ptr<BaseObject> model) :
    _action(&SceneManager::add_object), _model(model), _scene_manager(ManagerSolution::get_scene_manager()) { }

void AddModelCommand::execute()
{
    (*_scene_manager.*_action)(_model);
}

// === Удаление модели ===
RemoveModelCommand::RemoveModelCommand(size_t id) :
    _action(&SceneManager::remove_object), _id(id), _scene_manager(ManagerSolution::get_scene_manager()) { }

void RemoveModelCommand::execute()
{
    (*_scene_manager.*_action)(_id);
}

// === Перемещение модели ===
MoveModelCommand::MoveModelCommand(size_t id, const MoveData &data) :
    _action(&TransformManager::move_object), _id(id), _data(data),
    _transform_manager(ManagerSolution::get_transform_manager()) { }

void MoveModelCommand::execute()
{
    (*_transform_manager.*_action)(_id, _data);
}

// === Вращение модели ===
RotateModelCommand::RotateModelCommand(size_t id, const RotateData &data) :
    _action(&TransformManager::rotate_object), _id(id), _data(data),
    _transform_manager(ManagerSolution::get_transform_manager()) { }

void RotateModelCommand::execute()
{
    (*_transform_manager.*_action)(_id, _data);
}


// === Масштабирование модели ===
ScaleModelCommand::ScaleModelCommand(size_t id, const ScaleData &data) :
    _action(&TransformManager::scale_object), _id(id), _data(data),
    _transform_manager(ManagerSolution::get_transform_manager()) { }

void ScaleModelCommand::execute()
{
    (*_transform_manager.*_action)(_id, _data);
}

// === Композиция моделей ===
ComposeCommand::ComposeCommand(std::vector<size_t> ids) :
    _action(&SceneManager::compose), _ids(ids), _scene_manager(ManagerSolution::get_scene_manager()) { }

void ComposeCommand::execute()
{
    (*_scene_manager.*_action)(_ids);
}

// === Центр модели ===
GetCenterModelCommand::GetCenterModelCommand(size_t id, Point &center) :
    _action(&SceneManager::get_center), _id(id), _center(center),
    _scene_manager(ManagerSolution::get_scene_manager()) { }

void GetCenterModelCommand::execute()
{
    (*_scene_manager.*_action)(_id, _center);
}
