//
// Created by Dmitriy Dudurev on 02.05.2026.
//

#include "TransformVisitor.h"

#include "Component/SceneObject/Camera/BaseCamera.h"
#include "Component/SceneObject/Model/Structure/BaseStructure.h"

TransformVisitor::TransformVisitor(std::shared_ptr<TransformAction> action) : _action(action) {}

TransformVisitor::~TransformVisitor() {}

void TransformVisitor::visit(BaseCamera &camera) const
{
    if (_action)
        camera.transform(_action);
}

void TransformVisitor::visit(std::shared_ptr<BaseStructure> structure) const
{
    if (_action)
        structure->transform(_action);
}
