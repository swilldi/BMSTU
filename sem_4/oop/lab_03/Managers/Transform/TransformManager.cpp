//
// Created by Dmitriy Dudurev on 01.05.2026.
//

#include "TransformManager.h"

#include "Managers/ManagerSolution.h"
#include "Visitor/Transform/Move/MoveVisitor.h"
#include "Visitor/Transform/Rotate/RotateVisitor.h"
#include "Visitor/Transform/Scale/ScaleVisitor.h"

void TransformManager::move_object(size_t id, const MoveData &data)
{
    auto scene_manger = ManagerSolution::get_scene_manager();
    auto object = scene_manger->get_object(id);

    auto visitor = std::make_shared<MoveVisitor>(data);
    object->accept(visitor);
}

void TransformManager::rotate_object(size_t id, const RotateData &data)
{
    auto scene_manger = ManagerSolution::get_scene_manager();
    auto object = scene_manger->get_object(id);

    auto visitor = std::make_shared<RotateVisitor>(data);
    object->accept(visitor);
}

void TransformManager::scale_object(size_t id, const ScaleData &data)
{
    auto scene_manger = ManagerSolution::get_scene_manager();
    auto object = scene_manger->get_object(id);

    auto visitor = std::make_shared<ScaleVisitor>(data);
    object->accept(visitor);
}

